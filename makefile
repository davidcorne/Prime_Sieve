#==============================================================================
#D A make file to make an executable project
#D Directory structure:
# +--PrimeSieve
# +--+--PrimeSieve
# +--+--+-- header files
# +--+--source
# +--+--+--application
# +--+--+--+-- application file (with int main() in)
# +--+--+--src
# +--+--+--+-- normal source files
# +--+--exe
# +--+--+-- executable file
# +--+--lib
# +--+--+-- library file
# +--+--obj
# +--+--+-- object files

#------------------------------------------------------------------------------
# Options to edit with specific project names
EXE = prime_finder
LIB = PrimeSieve
# OBJECTS must be in dependency order right depending on left, and preceded by
# obj/ eg obj/utility.o obj/file.o
OBJECTS = obj/Sieve.o obj/Naive.o obj/Prime.o
INCLUDES = -I. 

include $(DROPBOX)/Coding/MakeFiles/cpp.mk
#OP_FLAGS = -O2
# override varaibles here
