#include "AstNode.hpp"

bool LogicalEquivalence::eval() const
{
	return _left->eval() == _right->eval();
}