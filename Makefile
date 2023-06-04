##
## EPITECH PROJECT, 2023
## panoramix
## File description:
## Makefile
##

NAME		=		panoramix
NAME_DEBUG	=		panoramix_debug
TEST		=		unit_tests

MAIN		=		main.c							\

SRC			= 	error_handling.c		\
						panoramix.c					\
						villager_method.c		\
						druid_method.c 			\
						create_village.c 		\
						destroy_village.c		\
						init_condvar.c

SRC_TESTS   =

OBJ         =    $(SRC:%.c=obj/build/%.o) $(MAIN:%.c=obj/build/%.o)
OBJ_DEBUG   =    $(SRC:%.c=obj/debug/%.o) $(MAIN:%.c=obj/debug/%.o)
OBJ_TEST    =    $(SRC:%.c=obj/debug/%.o) $(SRC_TEST:%.c=obj/tests/%.o)

CFLAGS    	=    -Wall -Wextra

CPPFLAGS    	=    -iquote ./includes/
LDFLAGSTEST    	+=   --coverage -lcriterion
LDFLAGS        	= 	-lpthread

RM          =	rm -rf

CC          =   gcc

all:	$(NAME)

obj/build/%.o:	sources/%.c
	@mkdir -p $(@D)
	$(CC) -o $@ $< -c $(CFLAGS) $(CPPFLAGS)

obj/debug/%.o:    sources/%.c
	@mkdir -p $(@D)
	$(CC) -o $@ $< -c $(CFLAGS) $(CPPFLAGS)

obj/tests/%.o:    tests/%.c
	@mkdir -p $(@D)
	$(CC) -o $@ $< -c $(CFLAGS) $(CPPFLAGS)

$(NAME):    $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

$(NAME_DEBUG): CFLAGS += -g3
$(NAME_DEBUG): $(OBJ_DEBUG)
	$(CC) -o $(NAME) $(OBJ_DEBUG) $(LDFLAGS)

$(TEST): $(OBJ_TEST)
	$(CC) -o $(TEST) $(OBJ_TEST) $(LDFLAGS) $(LDFLAGSTEST)

clean_cov:
	$(RM) $(OBJ:.o=.gcda) $(OBJ_TEST:.o=.gcda) $(OBJ_DEBUG:.o=.gcda)

clean:
	$(RM) $(OBJ) $(OBJ_TEST) $(OBJ_DEBUG)

fclean:    clean
	$(RM) $(NAME) $(NAME_DEBUG) $(TEST)
	$(RM) obj

re:    fclean all

tests_run: clean_cov $(TEST)
	./$(TEST)

.PHONY:    all clean fclean re clean_cov
