#include "AstNode.hpp"

Variable::Variable(char name, VarPtr var)
: _name(name), _var(var)
{
}

bool Variable::eval() const
{
	return *_var;
}

std::vector<std::string> Variable::to_strings() const
{
	return std::vector<std::string>{std::string(1, _name)};
}

AstNode::AstNodePtr Variable::transform()
{
	return nullptr;
}
