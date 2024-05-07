#include "AstNode.hpp"

bool ExclusiveDisjunction::eval() const
{
	return _left->eval() != _right->eval();
}

AstNode::AstNodePtr ExclusiveDisjunction::transform()
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
	
	return std::make_shared<Negation>(std::make_shared<LogicalEquivalence>('=', _left, _right));
}
