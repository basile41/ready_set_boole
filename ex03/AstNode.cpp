#include "AstNode.hpp"
#include <iostream>
#include <algorithm>

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

static std::vector<std::string> merge_strings(const std::vector<std::string> &left, const std::vector<std::string> &right)
{
	std::vector<std::string> result;
	size_t size_max = std::max(left.size(), right.size());
	for (size_t i = 0; i < size_max; i++)
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

std::vector<std::string> BinaryOperator::to_strings() const
{
	std::vector<std::string> left;
	std::vector<std::string> right;
	std::vector<std::string> result;

	const std::vector<std::string> left_strings = _left->to_strings();
	const std::vector<std::string> right_strings = _right->to_strings();
	size_t left_size = left_strings[0].size() / 2;
	size_t right_size = std::find_if_not(right_strings[0].begin(), right_strings[0].end(), isspace) - right_strings[0].begin();


	std::string spaces(left_strings.size(), ' ');
	// std::cerr << "spaces.size() = " << spaces.size() << std::endl;
	for (size_t i = 0; i <= left_size; i++)
		left.push_back(spaces + std::string(left_size - i, ' ') + '/' + std::string(i, ' '));
	for (const std::string &l: left_strings)
		left.push_back(l + " ");
	right_size = std::find_if_not(right_strings[0].begin(), right_strings[0].end(), isspace) - right_strings[0].begin();
	spaces = std::string(right_strings.size(), ' ');
	for (size_t i = 0; i <= right_size; i++)
		right.push_back(std::string(i, ' ') + "\\" + std::string(right_size - i, ' ') + spaces);
	for (const std::string &r: right_strings)
		right.push_back(" " + r);
	result = merge_strings(left, right);

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