#include "Ast.hpp"
#include <stack>
#include <stdexcept>
#include <iostream>

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
				throw std::runtime_error("Invalid formula (unexpected character)");
			AstNodePtr right = std::move(nodes_stack.top());
			nodes_stack.pop();
			if (c == '!')
			{
				AstNodePtr operator_node = createOperator(c, std::move(right));
				nodes_stack.push(std::move(operator_node));
			}
			else
			{
				if (nodes_stack.size() < 1)
					throw std::runtime_error("Invalid formula (unexpected character)");
				AstNodePtr left = std::move(nodes_stack.top());
				nodes_stack.pop();
				AstNodePtr operator_node = createOperator(c, std::move(left), std::move(right));
				nodes_stack.push(std::move(operator_node));
			}
		}
	}
	if (nodes_stack.size() == 1)
		_root = std::move(nodes_stack.top());
	else
		throw std::runtime_error("Invalid formula (too many operands)");
	
}

bool Ast::eval() const
{
	return _root->eval();
}

void Ast::print() const
{
	for (const std::string &s : _root->to_strings())
	{
		std::cout << s << std::endl;
	}
}

Ast::AstNodePtr Ast::createOperator(char op, AstNodePtr left, AstNodePtr right)
{
	switch (op)
	{
		case '!':
			return std::make_shared<Negation>(std::move(left));
		case '&':
			return std::make_shared<Conjunction>(op, std::move(left), std::move(right));
		case '|':
			return std::make_shared<Disjunction>(op, std::move(left), std::move(right));
		case '^':
			return std::make_shared<ExclusiveDisjunction>(op, std::move(left), std::move(right));
		case '>':
			return std::make_shared<MaterialCondition>(op, std::move(left), std::move(right));
		case '=':
			return std::make_shared<LogicalEquivalence>(op, std::move(left), std::move(right));
		default:
			throw std::runtime_error("Invalid character");
	}
}

Ast::AstNodePtr Ast::createValue(bool value)
{
	return std::make_shared<Value>(value);
}
