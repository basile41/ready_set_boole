
NAME			=	boolean_evaluation

INC				=	-I .

SRC_PATH		=	./
OBJ_PATH		=	./obj/

OBJ_DIRS		=	$(OBJ_PATH)

SRC				=	main.cpp \
					eval_formula.cpp \
					AstNode.cpp \
					Ast.cpp

OBJ				=	$(addprefix $(OBJ_PATH),$(SRC:.cpp=.o))
DEPS			=	$(addprefix $(OBJ_PATH),$(SRC:.cpp=.d))

CXX				=	c++
CXXFLAGS		=	-MMD -Wall -Wextra -Werror

all:				$(NAME)

$(OBJ_DIRS):
					@mkdir -p $(OBJ_DIRS)
					
$(OBJ_PATH)%.o:		$(SRC_PATH)%.cpp
					$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

$(NAME):			$(OBJ_DIRS) $(OBJ)
					$(CXX) $(OBJ) -o $@

clean:				
					rm -rf $(OBJ_PATH)

fclean:				clean
					rm -f $(NAME)

re:					fclean
					make all
					
-include			$(DEPS)

.PHONY:				all clean fclean re