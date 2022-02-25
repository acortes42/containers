# **************************************************************************** #

## VARIABLES ##

# COMPILATION #

CC			=	 clang++

CC_FLAGS	=	 -Wall -Wextra -Werror -std=c++98

# DELETE #

RM			=	rm -rf


# DIRECTORIES #

DIR_SRCS	=	./srcs/

DIR_OBJS	=	./compiled_objs/


# FILES #

SRCS			=	srcs/map.cpp \
					srcs/stack.cpp \
					srcs/vector.cpp

MAIN			=	srcs/main.cpp

TEST_MAIN		= 	srcs/test_main.cpp

# COMPILED_SOURCES #

OBJS 				=	${SRCS: .c =.o}

NAME 		=	containers


# **************************************************************************** #

## RULES ##

all:			$(NAME)

# RULES #

$(NAME):		$(OBJS) includes/containers.hpp
		@mkdir -p ${DIR_OBJS}
		@${CC} ${CFLAGS} -c ${SRCS} ${MAIN}
		@mv -f *.o ${DIR_OBJS}
		@$(RM) *.o
		@$(CC) $(CC_FLAGS) $(SRCS) ${MAIN} -o ${NAME}

# OBLIGATORY PART #

clean:
				@$(RM) $(DIR_OBJS)
				@echo "$(_RED) '"$(DIR_OBJS)"' has been deleted.🗑️"
				@$(RM) *.o

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) *.out
				@echo "$(_RED) '"$(NAME)"' has been deleted.🗑️"

re:				fclean all

debug: 			$(OBJS) includes/containers.hpp
		@mkdir -p ${DIR_OBJS}
		@${CC} ${CFLAGS} -g -c ${SRCS} ${MAIN}
		@mv *.o compiled_objs
		@$(CC) $(CC_FLAGS) $(SRCS) ${MAIN} -o ${NAME}

test:	$(OBJS) includes/containers.hpp
		@mkdir -p ${DIR_OBJS}
		@${CC} ${CFLAGS} -c ${SRCS} ${MAIN}
		@mv -f *.o ${DIR_OBJS}
		@$(RM) *.o
		@$(CC) $(CC_FLAGS) $(SRCS) ${TEST_MAIN} -o ${NAME}

# PHONY #

.PHONY:			all clean fclean re
