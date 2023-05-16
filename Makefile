all: clean main 
# gcc -g main.c -o main sources/node.c sources/list.c sources/matrix.c sources/position.c

main: objects/main.o objects/position.o objects/node.o objects/list.o objects/matrix.o
	gcc -g objects/main.o objects/position.o objects/node.o objects/list.o objects/matrix.o -o main
	@echo
	@echo Programa 1 compilado! Nome do arquivo executavel: main1
	@echo


objects/main.o: main.c headers/position.h headers/node.h headers/list.h headers/matrix.h
	gcc -g main.c -o objects/main.o -c -Wall

objects/position.o: sources/position.c headers/position.h
	gcc -g sources/position.c -o objects/position.o -c -Wall

objects/node.o: sources/node.c headers/node.h
	gcc -g sources/node.c -o objects/node.o -c -Wall

objects/list.o: sources/list.c headers/list.h
	gcc -g sources/list.c -o objects/list.o -c -Wall

objects/matrix.o: sources/matrix.c headers/matrix.h
	gcc -g sources/matrix.c -o objects/matrix.o -c -Wall


org: clean
	rm -r sources
	rm -r headers

	mkdir sources
	mkdir headers

	mv *.c sources/
	mv *.h headers/
	mv sources/main.c sources/..

	@echo Organizado!
	@echo

clean:
	rm -rf objetos/*.o *~ main 