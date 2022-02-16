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
					srcs/vector.cpp \
					srcs/main.cpp

# COMPILED_SOURCES #

OBJS 		=	${SRCS: .c =.o}

NAME 		=	containers


# **************************************************************************** #

## RULES ##

all:			$(NAME)

# RULES #

$(NAME):		$(OBJS) includes/containers.hpp
		@mkdir -p ${DIR_OBJS}
		@${CC} ${CFLAGS} -c ${SRCS}
		@mv *.o compiled_objs
		@$(CC) $(CC_FLAGS) $(SRCS) -o ${NAME}

# OBLIGATORY PART #

clean:
				@$(RM) $(DIR_OBJS)
				@echo "$(_RED) '"$(DIR_OBJS)"' has been deleted.🗑️"

fclean:			clean
				@$(RM) $(NAME)
				@$(RM) *.out
				@echo "$(_RED) '"$(NAME)"' has been deleted.🗑️"

re:				fclean all

debug: 			$(OBJS) includes/containers.hpp
		@mkdir -p ${DIR_OBJS}
		@${CC} ${CFLAGS} -g -c ${SRCS}
		@mv *.o compiled_objs
		@$(CC) $(CC_FLAGS) $(SRCS) -o ${NAME}

# PHONY #

.PHONY:			all clean fclean re
