all: clean main 


main: objects/main.o objects/position.o objects/node.o objects/list.o objects/matrix.o
	gcc -o main objects/main.o objects/position.o objects/node.o objects/list.o objects/matrix.o 
	@echo
	@echo Programa 1 compilado! Nome do arquivo executavel: main1
	@echo


objects/main.o: main.c headers/position.h headers/node.h headers/list.h headers/matrix.h
	gcc -o objects/main.o main.c -c -Wall

objects/position.o: sources/position.c headers/position.h
	gcc -o objects/position.o sources/position.c -c -Wall

objects/node.o: sources/node.c headers/node.h
	gcc -o objects/node.o sources/node.c -c -Wall

objects/list.o: sources/list.c headers/list.h
	gcc -o objects/list.o sources/list.c -c -Wall

objects/matrix.o: sources/matrix.c headers/matrix.h
	gcc -o objects/matrix.o sources/matrix.c -c -Wall


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