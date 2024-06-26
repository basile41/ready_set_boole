
#ifndef ASTNODE_HPP
#define ASTNODE_HPP

#include <memory>
#include <vector>
#include <string>

class AstNode
{
public:
	typedef std::shared_ptr<AstNode> AstNodePtr;


	virtual ~AstNode() = default;
	virtual bool eval() const = 0;
	virtual std::vector<std::string> to_strings() const = 0;
};

class Negation : public AstNode
{
public:
	Negation(AstNodePtr node);
	bool eval() const override;
	std::vector<std::string> to_strings() const override;
private:
	AstNodePtr _node;
};

class BinaryOperator : public AstNode
{
public:
	BinaryOperator(char op, AstNodePtr left, AstNodePtr right);
	std::vector<std::string> to_strings() const override;
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
	std::vector<std::string> to_strings() const override;
private:
	bool _value;
};

#endif /* ASTNODE_HPP */
