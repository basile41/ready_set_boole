#include "AstNode.hpp"
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
	std::vector<std::string> node = _node->to_strings();
	std::vector<std::string> result;
	for (const std::string &n: node)
	{
		result.push_back("!" + n);
	}
	return result;
}

BinaryOperator::BinaryOperator(char op, AstNodePtr left, AstNodePtr right)
: op(op), _left(std::move(left)), _right(std::move(right))
{
}

std::vector<std::string> BinaryOperator::to_strings() const
{
	std::vector<std::string> left;
	std::vector<std::string> right;
	std::vector<std::string> result;

	const std::vector<std::string> left_strings = _left->to_strings();
	const std::vector<std::string> right_strings = _right->to_strings();
	size_t left_size = left_strings[0].size();
	// std::cout << "left_size = " << left_size << std::endl;
	// for (const std::string &l: left_strings)
	// 	std::cout << l << std::endl;
	size_t right_size = right_strings[0].size();
	// std::cout << "right_size = " << right_size << std::endl;
	// for (const std::string &r: right_strings)
	// 	std::cout << r << std::endl;

	std::string spaces(left_strings.size(), ' ');
	// std::cerr << "spaces.size() = " << spaces.size() << std::endl;
	for (size_t i = 0; i < left_strings.size(); i++)
		left.push_back(spaces + std::string(left_size - i, ' ') + '/' + std::string(i, ' '));
	for (const std::string &l: left_strings)
		left.push_back(" " + l + " ");
	spaces = std::string(right_strings.size(), ' ');
	for (size_t i = 0; i < right_strings.size(); i++)
		right.push_back(std::string(i, ' ') + "\\" + std::string(right_size - i, ' ') + spaces);
	for (const std::string &r: right_strings)
		right.push_back(" " + r + " ");
	size_t size_max = std::max(left.size(), right.size());

	result.push_back(std::string(left.size()+1, ' ') + op + std::string(right.size()+1, ' '));
	for (size_t i = 0; i <= size_max; i++)
	{
		std::string line;
		if (i < left.size())
			line += left[i];
		else
			line += std::string(left[0].size(), ' ');
		line += ' ';
		if (i < right.size())
			line += right[i];
		else
			line += std::string(right[0].size(), ' ');
		result.push_back(line);
	}

	return result;
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

std::vector<std::string> Value::to_strings() const
{
	return std::vector<std::string>{value ? "1" : "0"};
}