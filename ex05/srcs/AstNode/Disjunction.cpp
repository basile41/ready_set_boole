#include "AstNode.hpp"

bool Disjunction::eval() const
{
	return _left->eval() || _right->eval();
}