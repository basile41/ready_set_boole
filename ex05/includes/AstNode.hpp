#ifndef ASTNODE_HPP
#define ASTNODE_HPP

#include <memory>
#include <vector>
#include <string>

// Base class for all nodes in the AST

class AstNode
{
public:
	typedef std::unique_ptr<AstNode> AstNodePtr;

	virtual ~AstNode() = default;
	virtual bool eval() const = 0;
	virtual std::vector<std::string> to_strings() const = 0;
	virtual AstNodePtr transform() = 0;
protected:
	std::vector<std::string> left_branch(const std::vector<std::string> &left_strings) const;
	std::vector<std::string> right_branch(const std::vector<std::string> &right_strings) const;
	std::vector<std::string> merge_strings(const std::vector<std::string> &left, const std::vector<std::string> &right, char op) const;
};

// Derived classes for each type of node in the AST

	// Unary operators

class Negation : public AstNode
{
public:
	Negation(AstNodePtr node);
	bool eval() const override;
	std::vector<std::string> to_strings() const override;
	AstNodePtr transform() override;
private:
	AstNodePtr _node;
};

	// Binary operators

class BinaryOperator : public AstNode
{
public:
	BinaryOperator(char op, AstNodePtr left, AstNodePtr right);
	std::vector<std::string> to_strings() const override;
	AstNodePtr transform() override;

protected:
	char _op;
	AstNodePtr _left;
	AstNodePtr _right;
};

class Conjunction : public BinaryOperator
{
public:
	using BinaryOperator::BinaryOperator;
	bool eval() const override;
};

class Disjunction : public BinaryOperator
{
public:
	using BinaryOperator::BinaryOperator;
	bool eval() const override;
};

class ExclusiveDisjunction : public BinaryOperator
{
public:
	using BinaryOperator::BinaryOperator;
	bool eval() const override;
};

class MaterialCondition : public BinaryOperator
{
public:
	using BinaryOperator::BinaryOperator;
	bool eval() const override;
	AstNodePtr transform() override;
};

class LogicalEquivalence : public BinaryOperator
{
public:
	using BinaryOperator::BinaryOperator;
	bool eval() const override;
};

	// Leaf nodes

class Value : public AstNode
{
public:
	Value(bool value);
	bool eval() const override;
	std::vector<std::string> to_strings() const override;
	AstNodePtr transform() override;
protected:
	bool _value;
};

class Variable : public AstNode
{
public:
	typedef std::shared_ptr<bool> VarPtr;

	Variable(char name, VarPtr var);
	bool eval() const override;
	std::vector<std::string> to_strings() const override;
	AstNodePtr transform() override;
private:
	char _name;
	VarPtr _var;
};

#endif /* ASTNODE_HPP */
