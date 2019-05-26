#include "Tree_expression.h"

bool Tree_expression::flip(float probability) {
	if (rand() / RAND_MAX < probability)
		return true;
	else
		return false;
}

Tree_expression::Tree_expression()
{
	std::vector<int> memory_operation;
	bool find_open_bracket = false;
	ptrdiff_t  _list_stage = OPEN_BRACKET;
	do {
		switch (_list_stage) {
		case OPEN_BRACKET: {

			_list_stage = OPERATION;
			information_tree number;
			number.i_number = '(';
			memory.emplace_back(number);
			data_tree result = { NULL, NULL, NULL, &memory.back().i_number };
			list.emplace_back(result);
			memory_operation.push_back(OPEN_BRACKET);
			break;
		}
		case OPERATION: {
			_list_stage = (rand() % 2) * 2;

			information_tree number;
			number.i_number = _list_operation[rand() % length_list_operation];
			memory.emplace_back(number);
			data_tree result = { NULL, NULL, &memory.back().i_number, NULL };
			list.emplace_back(result);

			//tree.push_back(&list.back());
			memory_operation.push_back(OPERATION);
			break;
		}

		case NUMBER:
			if (memory_operation.back() == NUMBER) {
				_list_stage = CLOSE_BRACKET;
				information_tree number;
				number.f_number = (float)rand() / RAND_MAX;
				memory.emplace_back(number);
				data_tree result = { &memory.back().f_number, NULL, NULL, NULL };
				list.emplace_back(result);
				//list.emplace_back(rand() % 9 + 48);
				//tree.push_back(&list.back());
				memory_operation.push_back(NUMBER);
			}
			else {
				_list_stage = (rand() % 2) * 2;
				information_tree number;
				number.f_number = (float)rand() / RAND_MAX;
				memory.emplace_back(number);
				data_tree result = { &memory.back().f_number, NULL, NULL, NULL };
				list.emplace_back(result);
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

						information_tree number;
						number.i_number = ')';
						memory.emplace_back(number);
						data_tree result = { NULL, NULL, NULL, &memory.back().i_number };
						list.emplace_back(result);

						//list.emplace_back(')');
						end_iter = start_iter + 1;
						find_open_bracket = false;
					}
					else if (memory_operation[end_iter] == OPERATION) {
						_list_stage = NUMBER;
						
						information_tree number;
						number.i_number = ')';
						memory.emplace_back(number);
						data_tree result = { NULL, NULL, NULL, &memory.back().i_number };
						list.emplace_back(result);

						//list.emplace_back(')');
						memory_operation.push_back(NUMBER);
						end_iter = start_iter + 1;
						find_open_bracket = false;
					}

				}
				if (memory_operation.empty()) {
					information_tree number;
					number.i_number = ')';
					memory.emplace_back(number);
					data_tree result = { NULL, NULL, NULL, &memory.back().i_number };
					list.emplace_back(result);
				//	list.emplace_back(')');
				}
			}
			break;
		}
	} while (memory_operation.size() > 0);
}



ptrdiff_t Tree_expression::calculateTree() {
	result = 0;
	bool operation, number_1, number_2;
	operation = number_1 = number_2 = 0;

	std::list< information_tree> _memory(this->memory);
	std::list<data_tree> _list(this->list);
	auto j = _memory.begin();
	for (auto i = _list.begin(); i != _list.end(); i++, j++) {
		if (i->operation || operation) {
			if (i->number || number_1) {
				if (i->number || number_2) {
					number_2 = true;
				}
				else
					operation = number_1 = false;
				number_1 = true;
			}else
				operation = number_1 = false;
			operation = true;
		}
		if (number_2) {
			_list.erase(i);
			_memory.erase(j);
			float_t number_2 = *i->number;
			_list.erase(i);
			_memory.erase(j);
			float_t number_1 = *i->number;
			_list.erase(i);
			_memory.erase(j);
			uint32_t operation = *i->operation;
			_list.erase(i);
			_memory.erase(j);
			switch (operation) {
			case MINUS:
				i->bracket = NULL;
				j->f_number = number_1 - number_2;
				i->number = &j->f_number;
				break;
			case PLUS:
				i->bracket = NULL;
				j->f_number = number_1 + number_2;
				i->number = &j->f_number;
				break;
			case DIVIDE:
				i->bracket = NULL;
				j->f_number = number_1 / number_2;
				i->number = &j->f_number;
				break;

			case MULTIPLY:
				i->bracket = NULL;
				j->f_number = number_1 * number_2;
				i->number = &j->f_number;
				break;
			}

			operation = number_1 = number_2 = false;
		}
	}
	result = *_list.begin()->number;
	return result;
}


Tree_expression::~Tree_expression()
{
}
