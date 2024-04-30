#include "AstNode.hpp"

bool MaterialCondition::eval() const
{
	return !_left->eval() || _right->eval();
}

// AstNode::AstNodePtr MaterialCondition::transform()
// {
// 	AstNodePtr new_left = _left->transform();
// 	AstNodePtr new_right = _right->transform();

// 	while (new_left || new_right)
// 	{
// 		if (new_left)
// 		{
// 			_left = std::move(new_left);
// 			new_left = _left->transform();
// 		}
// 		if (new_right)
// 		{
// 			_right = std::move(new_right);
// 			new_right = _right->transform();
// 		}
// 	}
// 	return nullptr;
// }
