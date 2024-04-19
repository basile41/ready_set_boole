#include "Ast.hpp"
#include <stack>
#include <stdexcept>

Ast::Ast(const std::string &formula)
{
	std::stack<AstNodePtr> nodes_stack;

	for (char c : formula)
	{
		if (c == ' ')
			continue;
		if (c == '0' || c == '1')
		{
			nodes_stack.push(createValue(c == '1'));
		}
		else
		{
			if (nodes_stack.size() < 1)
				throw std::runtime_error("Invalid formula (empty stack)");
			AstNodePtr right = std::move(nodes_stack.top());
			nodes_stack.pop();
			if (c == '!')
			{
				nodes_stack.push(createOperator(c, std::move(right)));
			}
			else
			{
				if (nodes_stack.size() < 1)
					throw std::runtime_error("Invalid formula (empty stack)");
				AstNodePtr left = std::move(nodes_stack.top());
				nodes_stack.pop();
				nodes_stack.push(createOperator(c, std::move(left), std::move(right)));
			}
		}
	}
	if (nodes_stack.size() == 1)
		_root = std::move(nodes_stack.top());
	else
		throw std::runtime_error("Invalid formula (stack size)");
	
}

bool Ast::eval() const
{
	return _root->eval();
}

Ast::AstNodePtr Ast::createOperator(char op, AstNodePtr left, AstNodePtr right)
{
	switch (op)
	{
		case '!':
			return std::make_unique<Negation>(std::move(left));
		case '&':
			return std::make_unique<Conjunction>(op, std::move(left), std::move(right));
		case '|':
			return std::make_unique<Disjunction>(op, std::move(left), std::move(right));
		case '^':
			return std::make_unique<ExclusiveDisjunction>(op, std::move(left), std::move(right));
		case '>':
			return std::make_unique<MaterialCondition>(op, std::move(left), std::move(right));
		case '=':
			return std::make_unique<LogicalEquivalence>(op, std::move(left), std::move(right));
		default:
			throw std::runtime_error("Invalid character");
	}
}

Ast::AstNodePtr Ast::createValue(bool value)
{
	return std::make_unique<Value>(value);
}
