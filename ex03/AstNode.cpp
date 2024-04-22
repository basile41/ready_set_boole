#include "AstNode.hpp"
#include <iostream>
#include <algorithm>

static std::vector<std::string> left_branch(const std::vector<std::string> &left_strings)
{
	std::vector<std::string> left;
	size_t size = std::find_if_not(left_strings[0].rbegin(), left_strings[0].rend(), isspace) - left_strings[0].rbegin();
	std::string spaces(left_strings[0].size() - size, ' ');

	for (size_t i = 0; i <= size; i++)
		left.push_back(spaces + std::string(size - i, ' ') + '/' + std::string(i, ' '));
	for (const std::string &l: left_strings)
		left.push_back(l + " ");
	return left;
}

static std::vector<std::string> right_branch(const std::vector<std::string> &right_strings)
{
	std::vector<std::string> right;
	size_t size = std::find_if_not(right_strings[0].begin(), right_strings[0].end(), isspace) - right_strings[0].begin();
	std::string spaces(right_strings[0].size() - size, ' ');

	for (size_t i = 0; i <= size; i++)
		right.push_back(std::string(i, ' ') + "\\" + std::string(size - i, ' ') + spaces);
	for (const std::string &r: right_strings)
		right.push_back(" " + r);
	return right;
}

static std::vector<std::string> merge_strings(const std::vector<std::string> &left, const std::vector<std::string> &right, char op)
{
	std::vector<std::string> result;
	size_t size_max = std::max(left.size(), right.size());
	result.push_back(std::string(left[0].size(), ' ') + op + std::string(right[0].size(), ' '));
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

BinaryOperator::BinaryOperator(char op, AstNodePtr left, AstNodePtr right)
: op(op), _left(std::move(left)), _right(std::move(right))
{
}

std::vector<std::string> BinaryOperator::to_strings() const
{
	const std::vector<std::string> left_strings = _left->to_strings();
	const std::vector<std::string> right_strings = _right->to_strings();

	std::vector<std::string> left = left_branch(left_strings);
	std::vector<std::string> right = right_branch(right_strings);
	std::vector<std::string> result = merge_strings(left, right, op);

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