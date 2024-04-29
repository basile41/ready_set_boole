#include "AstNode.hpp"

bool MaterialCondition::eval() const
{
	return !_left->eval() || _right->eval();
}
