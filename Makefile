SRCS = main.c genetic.c
OBJS = ${SRCS:%.c=%.o}
NAME = main

# Linking step:
${NAME}: ${OBJS}
	gcc -g -fsanitize=address ${OBJS} -o ${NAME}

# Compilation step:
%.o: %.c math.h
	gcc -g -fsanitize=address -c $< -o $@

clean:
	rm -f genetic.o main.o

fclean: clean
	rm -f main

re: fclean ${NAME}
