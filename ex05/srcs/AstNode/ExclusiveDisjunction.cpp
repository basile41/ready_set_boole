#include "AstNode.hpp"

bool ExclusiveDisjunction::eval() const
{
	return _left->eval() != _right->eval();
}