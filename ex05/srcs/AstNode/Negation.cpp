# include "AstNode.hpp"
#include <iostream>

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
	if (Negation *neg = dynamic_cast<Negation*>(_node.get()))
	{
		return neg->_node;
	}
	if (Conjunction *conj = dynamic_cast<Conjunction*>(_node.get()))
	{
		AstNodePtr new_left = std::make_shared<Negation>(conj->getLeft());
		AstNodePtr new_right = std::make_shared<Negation>(conj->getRight());
		return std::make_shared<Disjunction>('|', std::move(new_left), std::move(new_right));
	}
	if (Disjunction *disj = dynamic_cast<Disjunction*>(_node.get()))
	{
		AstNodePtr new_left = std::make_shared<Negation>(disj->getLeft());
		AstNodePtr new_right = std::make_shared<Negation>(disj->getRight());
		return std::make_shared<Conjunction>('&', std::move(new_left), std::move(new_right));
	}
	return nullptr;
}

std::string Negation::toRPN() const
{
	return _node->toRPN() + "!";
}
