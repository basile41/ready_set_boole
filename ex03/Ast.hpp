#ifndef AST_HPP
#define AST_HPP

class Ast
{
public:
	Ast() {}
	Ast(const Ast&);
	~Ast() {}
	const Ast& operator=(const Ast&);

	void print() const;

private:
	
};

#endif /* AST_HPP */
