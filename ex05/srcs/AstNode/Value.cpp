#include "AstNode.hpp"

Value::Value(bool value)
: _value(value)
{
}

bool Value::eval() const
{
	return _value;
}

std::vector<std::string> Value::to_strings() const
{
	return std::vector<std::string>{_value ? "1" : "0"};
}

AstNode::AstNodePtr Value::transform()
{
	return nullptr;
}

std::string Value::toRPN() const
{
	return _value ? "1" : "0";
}
