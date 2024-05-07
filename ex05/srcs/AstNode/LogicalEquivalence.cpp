#include "AstNode.hpp"

bool LogicalEquivalence::eval() const
{
	return _left->eval() == _right->eval();
}

AstNode::AstNodePtr LogicalEquivalence::transform()
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
	AstNodePtr A = _left;
	AstNodePtr B = _right;
	AstNodePtr left = std::make_shared<MaterialCondition>('>', A, B);
	AstNodePtr right = std::make_shared<MaterialCondition>('>', B, A);
	AstNodePtr new_node = std::make_shared<Conjunction>('&', left, right);
	return new_node;
}
