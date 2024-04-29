#include "AstNode.hpp"
#include <iostream>
#include <algorithm>

std::vector<std::string> AstNode::left_branch(const std::vector<std::string> &left_strings) const
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

std::vector<std::string> AstNode::right_branch(const std::vector<std::string> &right_strings) const
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

std::vector<std::string> AstNode::merge_strings(const std::vector<std::string> &left, const std::vector<std::string> &right, char op) const
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
