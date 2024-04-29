# include "AstNode.hpp"

Negation::Negation(AstNodePtr node)
: _node(std::move(node))
{
}

bool Negation::eval() const
{
	return !_node->eval();
}

std::vector<std::string> Negation::to_strings() const
{
	std::vector<std::string> right_strings = _node->to_strings();
	std::vector<std::string> right = right_branch(right_strings);
	std::vector<std::string> result = merge_strings({""}, right, '!');
	return result;
}

AstNode::AstNodePtr Negation::transform()
{
	AstNodePtr new_node = _node->transform();
	while (new_node)
	{
		_node = std::move(new_node);
		new_node = _node->transform();
	}
	// si _node est un Negation, on retourne son noeud interne
	if (Negation *neg = dynamic_cast<Negation*>(_node.get()))
	{
		return std::move(neg->_node);
	}
	return nullptr;
}
