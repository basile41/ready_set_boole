#include "AstNode.hpp"
#include "Ast.hpp"
#include <iostream>
#include <memory>

bool MaterialCondition::eval() const
{
	return !_left->eval() || _right->eval();
}

AstNode::AstNodePtr MaterialCondition::transform()
{
	AstNodePtr new_left = _left->transform();
	AstNodePtr new_right = _right->transform();

	while (new_left)
	{
		_left = new_left;
		new_left = _left->transform();
	}
	while (new_right)
	{
		_right = new_right;
		new_right = _right->transform();
	}
	new_left = std::make_shared<Negation>(_left);
	AstNodePtr new_node = std::make_shared<Disjunction>('|', new_left, _right);
	return new_node;
}
