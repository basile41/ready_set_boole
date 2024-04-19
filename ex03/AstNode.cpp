#include "AstNode.hpp"

Negation::Negation(AstNodePtr node)
: _node(std::move(node))
{
}

bool Negation::eval() const
{
	return !_node->eval();
}

BinaryOperator::BinaryOperator(char op, AstNodePtr left, AstNodePtr right)
: op(op), _left(std::move(left)), _right(std::move(right))
{
}

bool Conjunction::eval() const
{
	return _left->eval() && _right->eval();
}

bool Disjunction::eval() const
{
	return _left->eval() || _right->eval();
}

bool ExclusiveDisjunction::eval() const
{
	return _left->eval() != _right->eval();
}

bool MaterialCondition::eval() const
{
	return !_left->eval() || _right->eval();
}

bool LogicalEquivalence::eval() const
{
	return _left->eval() == _right->eval();
}

Value::Value(bool value)
: value(value)
{
}

bool Value::eval() const
{
	return value;
}
