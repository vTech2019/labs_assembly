#pragma once

#include <iostream>
#include <list>
#include <vector>

const uint8_t _list_operation[] = { 45, 43, 42, 47 };
enum list_operation { MINUS = 45, PLUS = 43, MULTIPLY = 42, DIVIDE = 47 };
enum list_stage { OPEN_BRACKET, OPERATION, NUMBER, CLOSE_BRACKET };
#define length_list_operation  4
struct data_tree {
	float_t* number;
	uint32_t* symbol;
	uint32_t* operation;
	uint32_t* bracket;
};
union information_tree {
	float_t f_number;
	uint32_t i_number;
};
class Tree_expression
{

	ptrdiff_t result;
	//std::vector<size_t> symbols;
	//std::vector<uint8_t*> tree;
	std::list< information_tree> memory;
	std::list<data_tree> list;
public:
	std::list<data_tree>::iterator getList() {
		return list.begin();
	}
	std::list<data_tree>::iterator getEndList() {
		return list.end();
	}
	bool flip(float probability);
	Tree_expression();
	ptrdiff_t calculateTree();
	~Tree_expression();
};

