#include "AstNode.hpp"

BinaryOperator::BinaryOperator(char op, AstNodePtr left, AstNodePtr right)
: _op(op), _left(std::move(left)), _right(std::move(right))
{
}

std::vector<std::string> BinaryOperator::to_strings() const
{
	const std::vector<std::string> left_strings = _left->to_strings();
	const std::vector<std::string> right_strings = _right->to_strings();

	std::vector<std::string> left = AstNode::left_branch(left_strings);
	std::vector<std::string> right = AstNode::right_branch(right_strings);
	std::vector<std::string> result = AstNode::merge_strings(left, right, _op);

	return result;
}

AstNode::AstNodePtr BinaryOperator::transform()
{
	AstNodePtr new_left = _left->transform();
	AstNodePtr new_right = _right->transform();
	while (new_left || new_right)
	{
		if (new_left)
			_left = std::move(new_left);
		if (new_right)
			_right = std::move(new_right);
		new_left = _left->transform();
		new_right = _right->transform();
	}
	return nullptr;
}

std::string BinaryOperator::toRPN() const
{
	return _left->toRPN() + _right->toRPN() + _op;
}