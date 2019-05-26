// labs_assembly.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <list>
#include <vector>
#include "Tree_expression.h"

int main()
{
	for (size_t j = 0; j < 100; j++) {
		Tree_expression tree;
		for (auto i = tree.getList(); i != tree.getEndList(); i++) {
			if (i->symbol)
				std::cout << (uint8_t)*i->symbol;
			else if (i->bracket)
				std::cout << (uint8_t)*(i->bracket);
			else if (i->number)
				std::cout << *i->number;
			if (i->operation)
				std::cout << (uint8_t)*i->operation;
		}
		std::cout << std::endl;
		std::cout << tree.calculateTree()<<std::endl;
	}
	return 0;
}
