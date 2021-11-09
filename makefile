all: calc

calc: main.o bignum.o cmdline.o 
	g++ -std=c++11 -Wall -pedantic -g3 main.o bignum.o cmdline.o -o calc

main.o: main.cc bignum.h cmdline.h 
	g++ -std=c++11 -Wall -pedantic -g3 -c main.cc

bignum.o: bignum.cc bignum.h stack.h queue.h debug.h
	g++ -std=c++11 -Wall -pedantic -g3 -c bignum.cc

cmdline.o: cmdline.cc cmdline.h 
	g++ -std=c++11 -Wall -pedantic -g3 -c cmdline.cc

clean:
	$(RM) calc *.o