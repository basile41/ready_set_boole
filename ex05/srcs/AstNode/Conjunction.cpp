#include "AstNode.hpp"

bool Conjunction::eval() const
{
	return _left->eval() && _right->eval();
}