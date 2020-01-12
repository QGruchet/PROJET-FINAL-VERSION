ZIPNAME=GRUCHET_MECHRI

all: partie1 partie2

partie1: main1
	./main1 

partie2: main2
	./main2

main1: main1.o sequence.o distance.o
	gcc -Wall -o main1 main1.o sequence.o distance.o

main2: main2.o sequence.o distance.o famille.o
	gcc -Wall -o main2 main2.o sequence.o distance.o famille.o

main1.o: main1.c sequence.h
	gcc -Wall -c -g main1.c

sequence.o: sequence.c sequence.h
	gcc -Wall -c -g sequence.c 

distance.o: distance.c distance.h
	gcc -Wall -c -g distance.c

famille.o : famille.c famille.h
	gcc -Wall -c -g famille.c

leaks:  main1 main2
	valgrind --leak-check=full --show-leak-kinds=all  ./main2


clean:
	rm -rf *.o
	rm -rf main1 main2 
	rm -rf sequence.h.gch distance.h.gch
	rm -r Famille
	rm -rf *.tar
	ls -l


archive:
	tar -vcf ${ZIPNAME}.tar *.c *.h Makefile sequence
	ls -l