#include "Ast.hpp"
#include <stack>
#include <stdexcept>
#include <iostream>

Ast::Ast(const std::string &formula)
: _root(nullptr), _variables()
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
		else if (isupper(c))
		{
			nodes_stack.push(createVarNode(c));
		}
		else
		{
			if (nodes_stack.size() < 1)
				throw std::runtime_error("Invalid formula (unexpected character)");
			AstNodePtr right = std::move(nodes_stack.top());
			nodes_stack.pop();
			if (c == '!')
			{
				nodes_stack.push(createOperator(c, std::move(right)));
			}
			else
			{
				if (nodes_stack.size() < 1)
					throw std::runtime_error("Invalid formula (unexpected character)");
				AstNodePtr left = std::move(nodes_stack.top());
				nodes_stack.pop();
				nodes_stack.push(createOperator(c, std::move(left), std::move(right)));
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

Ast::AstNodePtr Ast::createVarNode(char var)
{
	return std::make_shared<Variable>(var, getVariable(var));
}

Ast::BoolPtr Ast::setVariable(char name, bool value)
{
	if (!isupper(name))
		throw std::runtime_error("Invalid variable name");
	auto it = _variables.find(name);
	if (it != _variables.end())
	{
		*it->second = value;
		return it->second;
	}
	else
		_variables[name] = std::make_shared<bool>(value);
	return _variables[name];
}

Ast::BoolPtr Ast::getVariable(char name)
{
	auto it = _variables.find(name);
	if (it == _variables.end())
	{
		BoolPtr var = setVariable(name);
		_variables[name] = var;
		return var;
	}
	return it->second;
}

void Ast::printTruthTable() const
{
	std::map<char, bool> saved_values;
	std::vector<char> vars;

	for (const auto &var : _variables)
	{
		saved_values[var.first] = *var.second;
		vars.push_back(var.first);
		*var.second = false;
		std::cout << "| " << var.first << " ";
	}
	std::cout << "| = |\n";
	for (size_t i = 0; i < vars.size(); i++)
		std::cout << "|---";
	std::cout << "|---|" << std::endl;

	for (int i = 0; i < (1 << vars.size()); i++)
	{
		for (size_t j = 0; j < vars.size(); j++)
		{
			bool value = i >> (vars.size() - 1 - j) & 1;
			auto it = _variables.find(vars[j]);
			*it->second = value;
			std::cout << "| " << value << " ";
		}
		std::cout << "| " << eval() << " |" << std::endl;
	}

}