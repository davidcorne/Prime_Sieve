SOURCE = sieve
EXE = prime_finder

UTEST = utest_$(SOURCE)
CC = g++
CC_OPTIONS = 

$(EXE).exe: $(EXE).cpp $(SOURCE).o
	$(CC) -c $(EXE).cpp
	$(CC) -o $(EXE).exe $(SOURCE).o $(EXE).o 

$(SOURCE).o: $(SOURCE).cpp $(SOURCE).h
	$(CC) -c $<

utest: $(UTEST).exe
	@echo ""
	@./$(UTEST).exe

$(UTEST).exe: $(UTEST).cpp $(SOURCE).o
	$(CC) $(UTEST).cpp -o $(UTEST).exe $(SOURCE).o 

clean: FRC
# clean the folder for push back to git
	rm -f *.o *.lib *.exe *.stackdump *~ \#*\#

FRC:

