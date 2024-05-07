NAME			=		ex05

#############################################################################
#																			#
#								COMPILER									#
#																			#
#############################################################################

CXX				=	g++

CXXFLAGS		=	-MMD -Wall -Wextra -Werror -g3

INC				=	-I includes/

SILENT			=	--no-print-directory

#############################################################################
#																			#
#									PATHS									#
#																			#
#############################################################################

SRCS_PATH		=	srcs/
OBJS_PATH		=	objs/
SRCS_AST		=	AstNode/

#############################################################################
#																			#
#									FILES									#
#																			#
#############################################################################

SRCS				=	main.cpp 				\
						negation_normal_form.cpp	\
						Ast.cpp 				\
						$(addprefix $(SRCS_AST),		\
							AstNode.cpp 				\
							Negation.cpp 				\
							BinaryOperator.cpp			\
							Conjunction.cpp				\
							Disjunction.cpp				\
							ExclusiveDisjunction.cpp	\
							LogicalEquivalence.cpp		\
							MaterialCondition.cpp		\
							Value.cpp					\
							Variable.cpp				\
						)
					

OBJS			=	$(addprefix $(OBJS_PATH), $(SRCS:.cpp=.o))

DEPS			=	$(OBJS:.o=.d)

#############################################################################
#																			#
#									RULES									#
#																			#
#############################################################################

all:				$(NAME)

${NAME}:			${OBJS}
					$(CXX) $(OBJS) -o $@

$(OBJS_PATH)%.o:	$(SRCS_PATH)%.cpp
					@mkdir -p $(dir $@)
					$(CXX) -MMD $(CXXFLAGS) -c $< -o $@ $(INC)

clean:
					@rm -rf $(OBJS_PATH)
					@echo "Objects cleaned!"
					
fclean:				clean
					@rm -f $(NAME)

re:					fclean
					@make all $(SILENT)

-include $(DEPS)
.PHONY:				all clean fclean re