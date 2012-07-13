SOURCE = sieve
EXE = prime_finder
CC = g++

$(EXE).exe: $(SOURCE).cpp 
	$(CC) $(SOURCE).cpp -o $(EXE).exe

clean: FRC
	rm -f *.o *.lib *.stackdump *~ \#*\#

FRC:

