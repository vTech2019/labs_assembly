#pragma once

#include <iostream>
#include <list>
#include <vector>

const uint8_t _list_operation[] = { 45, 43, 42, 47 };

enum symbols { a = 97, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z = 122 };
enum list_operation { MINUS = 45, PLUS = 43, MULTIPLY = 42, DIVIDE = 47 };
enum list_stage { OPEN_BRACKET, OPERATION, NUMBER, CLOSE_BRACKET };
#define length_list_operation  4
struct data_tree {
	float_t local_number;
	float_t* number;
	int32_t symbol;
	int32_t operation;
	int32_t bracket;
};
class Tree_expression
{

	float_t result;
	std::list<data_tree> list;
	std::vector<uint8_t> tree_symbols;
public:
	std::list<data_tree>::iterator getList() {
		return list.begin();
	}
	std::list<data_tree>::iterator getEndList() {
		return list.end();
	}
	std::list<data_tree>::const_iterator constGetList() {
		return list.cbegin();
	}
	std::list<data_tree>::const_iterator constGetEndList() {
		return list.cend();
	}
	std::vector<uint8_t>::iterator returnStartSymbols() {
		return tree_symbols.begin();
	}
	std::vector<uint8_t>::iterator returnEndSymbols() {
		return tree_symbols.end();
	}
	void push_info_tree_expression(data_tree data_tree, uint8_t symbol) {
		list.push_back(data_tree);
		if (symbol)
			tree_symbols.push_back(symbol);

	}
	bool flip(float probability);
	float_t calculateTree();
	Tree_expression(const Tree_expression& expr) {
		list=expr.list;
		tree_symbols = expr.tree_symbols;
		if (!list.empty()) {
			auto start = list.begin();
			auto end = list.end();
			while (start != end) {
				if (start->number)
					start->number = &start->local_number;
				start++;
			}
		}
	}
	Tree_expression();
	Tree_expression(bool generate);
	~Tree_expression();
};

class Tree_generation {
	std::vector<uint8_t> tree_symbols;
	Tree_expression* expression;
public:
	Tree_generation();
	Tree_generation(Tree_expression& main_expr) {
		expression = new Tree_expression;
		setTree(main_expr);
	}
	Tree_expression* getTreeExpression() {
		return expression;
	}
	void setTree(Tree_expression& main_expr) {
		auto i = main_expr.getList();
		auto end_i = main_expr.getEndList();
		auto s = main_expr.returnStartSymbols();
		auto end_s = main_expr.returnEndSymbols();
		uint8_t symbol = 0;
		while(i!=end_i){
			if (s != end_s) {
				symbol = *s;
				s++;
			}
			expression->push_info_tree_expression(*i, symbol);
			symbol = 0;
				i++;
		}
	}
	void setRandomSymbols() {
		auto end_list = expression->getEndList();
		auto end_symbols = expression->returnEndSymbols();
		for (auto j =  expression->returnStartSymbols(); j != end_symbols; j++) {
			float_t random_number = (float_t)rand() / RAND_MAX;
			for (auto i = expression->getList(); i != end_list; i++) {
				bool find = false;
				if (i->symbol)
					if ((i->symbol) == *j) {
						i->local_number = random_number;
						i->number = &i->local_number;
					}
		}
		}
	}
	~Tree_generation() {
		if (expression)
			delete (expression);
	};

};
