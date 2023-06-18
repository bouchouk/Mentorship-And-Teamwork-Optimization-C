SRCS = main.c genetic_fonctions.c merge_sort.c append.c population.c
OBJS = ${SRCS:%.c=%.o}
NAME = main

# Linking step:
${NAME}: ${OBJS}
	gcc -g ${OBJS} -o ${NAME}

# Compilation step:
%.o: %.c math.h
	gcc -g -c $< -o $@

clean:
	rm -f genetic_fonctions.o main.o merge_sort.o append.o population.c

fclean: clean
	rm -f main

re: fclean ${NAME}
