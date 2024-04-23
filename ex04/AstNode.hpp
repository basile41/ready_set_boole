#ifndef B4911E9D_A3C3_4F3E_A420_5476A73C8582
#define B4911E9D_A3C3_4F3E_A420_5476A73C8582

#ifndef ASTNODE_HPP
#define ASTNODE_HPP

#include <memory>
#include <vector>
#include <string>

class AstNode
{
public:
	typedef std::unique_ptr<AstNode> AstNodePtr;

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
private:
	char _name;
	VarPtr _var;
};

#endif /* ASTNODE_HPP */


#endif /* B4911E9D_A3C3_4F3E_A420_5476A73C8582 */
