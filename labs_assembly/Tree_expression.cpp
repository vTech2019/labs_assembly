#include "Tree_expression.h"

bool Tree_expression::flip(float probability) {
	if ((float)rand() / RAND_MAX < probability)
		return true;
	else
		return false;
}

Tree_expression::Tree_expression() {

};
Tree_expression::Tree_expression(bool generate)
{
	if (!generate)
		return;
	std::vector<int> memory_operation;
	bool find_open_bracket = false;
	ptrdiff_t  _list_stage = OPEN_BRACKET;
	do {
		switch (_list_stage) {
		case OPEN_BRACKET: {
			_list_stage = OPERATION;
			data_tree result = { 0.0f, NULL, -INT_MAX, -INT_MAX, '(' };
			list.emplace_back(result);
			memory_operation.push_back(OPEN_BRACKET);
			break;
		}
		case OPERATION: {
			_list_stage = (rand() % 2) * 2;
			data_tree result = { 0.0f, NULL, _list_operation[rand() % length_list_operation], -INT_MAX };
			list.emplace_back(result);

			//tree.push_back(&list.back());
			memory_operation.push_back(OPERATION);
			break;
		}

		case NUMBER:
			if (memory_operation.back() == NUMBER) {
				_list_stage = CLOSE_BRACKET;

				if (flip(0.5)) {
					data_tree result = { (float)rand() / RAND_MAX, NULL, -INT_MAX, -INT_MAX, -INT_MAX };
					result.number = &result.local_number;
					list.emplace_back(result);
				}
				else {
					uint32_t number = a + (int)((z - a) * (float)rand() / RAND_MAX);
					data_tree result = { NULL, NULL, number, -INT_MAX, -INT_MAX };
					list.emplace_back(result);
					bool find = false;
					for (auto i = tree_symbols.begin(); i != tree_symbols.end(); i++)
						if (*i == number)
							find = true;
					if (!find)
						tree_symbols.push_back(number);
				}
				//list.emplace_back(rand() % 9 + 48);
				//tree.push_back(&list.back());
				memory_operation.push_back(NUMBER);
			}
			else {
				_list_stage = (rand() % 2) * 2;

				if (flip(0.5)) {
					int32_t number = (float)rand() / RAND_MAX;
					data_tree result = { number, NULL, -INT_MAX, -INT_MAX, -INT_MAX };
					result.number = &result.local_number;
					list.emplace_back(result);
				}
				else {
					uint32_t number = a + (int)((z-a) * (float)rand() / RAND_MAX);
					bool find = false;
					for (auto i = tree_symbols.begin(); i != tree_symbols.end(); i++)
						if (*i == number)
							find = true;
					if (!find)
						tree_symbols.push_back(number);
					data_tree result = { NULL, NULL, number, -INT_MAX, -INT_MAX };
					list.emplace_back(result);
				}
				//list.emplace_back(rand() % 9 + 48);
				//tree.push_back(&list.back());
				memory_operation.push_back(NUMBER);
			}
			break;
		case CLOSE_BRACKET:
			//i--;
			for (int end_iter = memory_operation.size() - 1, start_iter = -1; end_iter != start_iter; end_iter--) {

				if (!find_open_bracket) {
					if (memory_operation[end_iter] == OPEN_BRACKET) {
						find_open_bracket = true;
					}
					if (memory_operation[end_iter] != CLOSE_BRACKET)
						memory_operation.erase(memory_operation.begin() + end_iter);
				}
				else {
					if (memory_operation[end_iter] == NUMBER) {
						_list_stage = CLOSE_BRACKET;

						uint32_t number = ')';
						data_tree result = { NULL, NULL, -INT_MAX, -INT_MAX, number };
						list.emplace_back(result);

						//list.emplace_back(')');
						end_iter = start_iter + 1;
						find_open_bracket = false;
					}
					else if (memory_operation[end_iter] == OPERATION) {
						_list_stage = NUMBER;
						
						uint32_t number = ')';
						data_tree result = { NULL, NULL, -INT_MAX, -INT_MAX, number };
						list.emplace_back(result);

						//list.emplace_back(')');
						memory_operation.push_back(NUMBER);
						end_iter = start_iter + 1;
						find_open_bracket = false;
					}

				}
				if (memory_operation.empty()) {
					uint32_t number = ')';
					data_tree result = { NULL, NULL, -INT_MAX, -INT_MAX, number };
					list.emplace_back(result);
				//	list.emplace_back(')');
				}
			}
			break;
		}
	} while (memory_operation.size() > 0);
}



float_t Tree_expression::calculateTree() {
	result = 0;
	bool find_operation, find_number_1, find_number_2 = false;
	std::list<data_tree> _list(this->list);
	for (auto i = _list.begin(); i != _list.end(); i++) {
		if (i->operation > 0)
			find_operation = true;
		else if (i->number)
			find_number_2 = find_number_1 ? true : false,
			find_number_1 = true;
		else
			find_operation = find_number_1 = find_number_2 = false;
		if (find_number_2 > 0) {
			auto tmp_i = i++;
			_list.erase(i);
			i = tmp_i;
			float_t number_2 = *i->number;
			tmp_i = i--;
			_list.erase(tmp_i);
			float_t number_1 = *i->number;
			tmp_i = i--;
			_list.erase(tmp_i);
			uint32_t operation = i->operation;
			tmp_i = i--;
			_list.erase(tmp_i);
			switch (operation) {
			case MINUS:
				i->bracket = -INT_MAX;
				*i->number = number_1 - number_2;
				break;
			case PLUS:
				i->bracket = -INT_MAX;
				*i->number = number_1 + number_2;
				break;
			case DIVIDE:
				i->bracket = -INT_MAX;
				*i->number = number_1 / number_2;
				break;

			case MULTIPLY:
				i->bracket = -INT_MAX;
				*i->number = number_1 * number_2;
				break;
			}
			i = _list.begin();
			find_operation = find_number_1 = find_number_2 = false;
		}
	}
	if (_list.begin()->number)
		result = *_list.begin()->number;
	return result;
}


Tree_expression::~Tree_expression()
{
	this->list.clear();
	this->tree_symbols.clear();
}

Tree_generation::Tree_generation()
{
}

