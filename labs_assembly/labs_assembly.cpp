// labs_assembly.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <list>
#include <vector>
#include "Tree_expression.h"

int main()
{
	std::list<Tree_expression> tree;
	std::list<Tree_generation> tree_gen;
	for (size_t j = 0; j < 100; j++) {
		Tree_expression curent_expression(true);
		tree.emplace_back(curent_expression);
		Tree_generation tmp_tree(tree.back());
	
		tree_gen.emplace_back(tmp_tree);
		tree_gen.back().setRandomSymbols();
		for (auto i = tree.back().getList(); i != tree.back().getEndList(); i++) {
			if (i->symbol > 0)
				std::cout << (uint8_t)i->symbol <<' ';
			else if (i->bracket > 0)
				std::cout << (uint8_t)(i->bracket) << ' ';
			else if (i->number)
				std::cout << *i->number << ' ';
			if (i->operation > 0)
				std::cout << (uint8_t)i->operation << ' ';
		}
		std::cout << std::endl;
		std::cout << tree_gen.back().getTreeExpression()->calculateTree()<<std::endl;
	}
	return 0;
}
