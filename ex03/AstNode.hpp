
#ifndef ASTNODE_HPP
#define ASTNODE_HPP

#include <memory>

class AstNode
{
public:
	typedef std::unique_ptr<AstNode> AstNodePtr;


	virtual ~AstNode() = default;
	virtual bool eval() const = 0;
};

class Negation : public AstNode
{
public:
	Negation(AstNodePtr node);
	bool eval() const override;
private:
	AstNodePtr _node;
};

class BinaryOperator : public AstNode
{
public:
	BinaryOperator(char op, AstNodePtr left, AstNodePtr right);
protected:
	char op;
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
};

class LogicalEquivalence : public BinaryOperator
{
public:
	using BinaryOperator::BinaryOperator;
	bool eval() const override;
};

class Value : public AstNode
{
public:
	Value(bool value);
	bool eval() const override;
private:
	bool value;
};

#endif /* ASTNODE_HPP */