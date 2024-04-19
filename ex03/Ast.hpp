#ifndef AST_HPP
# define AST_HPP

# include <string>
# include <memory>
# include "AstNode.hpp"

class Ast
{
public:
	typedef AstNode::AstNodePtr AstNodePtr;

	Ast(const std::string &formula);

	
	bool eval() const;
private:
	static AstNodePtr createOperator(char op, AstNodePtr left, AstNodePtr right = nullptr);
	static AstNodePtr createValue(bool value);
	AstNodePtr _root;
};

#endif /* AST_HPP */
