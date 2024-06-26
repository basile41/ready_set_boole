#ifndef AST_HPP
# define AST_HPP

# include <string>
# include <map>
# include <memory>
# include "AstNode.hpp"

class Ast
{
public:
	typedef AstNode::AstNodePtr AstNodePtr;
	typedef std::shared_ptr<bool> BoolPtr;


	Ast(const std::string &formula);

	bool eval() const;
	void print() const;
	void printTruthTable() const;
	std::string toRPN() const;

	BoolPtr setVariable(char var, bool value = false);
	BoolPtr getVariable(char var);
private:
	static AstNodePtr createOperator(char op, AstNodePtr left, AstNodePtr right = nullptr);
	static AstNodePtr createValue(bool value);
	AstNodePtr createVarNode(char var);

	AstNodePtr _root;
	std::map<char, BoolPtr> _variables;
};

#endif /* AST_HPP */