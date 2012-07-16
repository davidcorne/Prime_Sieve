OBJECTS = sieve.o naive.o prime.o
LIB = prime.lib
EXE = prime_finder

UTEST = utest_primes
CC = g++
CC_OPTIONS = 

$(EXE).exe: $(EXE).cpp $(OBJECTS) $(LIB)
	$(CC) -c $(EXE).cpp
	$(CC) -o $(EXE).exe $(EXE).o $(LIB)

$(LIB): $(OBJECTS)
	ar ruvs $(LIB) $(OBJECTS)

naive.o: naive.cpp naive.h prime.o large_int.h sieve.o
	$(CC) -c naive.cpp

sieve.o: sieve.cpp sieve.h prime.o large_int.h
	$(CC) -c sieve.cpp

prime.o: prime.cpp prime.h large_int.h
	$(CC) -c prime.cpp


utest: $(UTEST).exe
	@echo ""
	@./$(UTEST).exe

$(UTEST).exe: $(UTEST).cpp $(OBJECTS)
	$(CC) $(UTEST).cpp -o $(UTEST).exe $(OBJECTS)

commit: clean
# new git commit, doesn't work through cygwin
	@git add *; \
	echo "Name this commit"; \
	read name; \
	git commit -m "$$name"; \
	git push -u origin master

clean: FRC
# clean the folder for push back to git/neatness
	rm -f *.o *.lib *.exe *.stackdump *~ \#*\#

FRC:

