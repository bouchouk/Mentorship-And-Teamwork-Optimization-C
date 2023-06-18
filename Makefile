SRCS = main.c genetic.c merge_sort.c
OBJS = ${SRCS:%.c=%.o}
NAME = main

# Linking step:
${NAME}: ${OBJS}
	gcc -g ${OBJS} -o ${NAME}

# Compilation step:
%.o: %.c math.h
	gcc -g -c $< -o $@

clean:
	rm -f genetic.o main.o merge_sort.o

fclean: clean
	rm -f main

re: fclean ${NAME}
