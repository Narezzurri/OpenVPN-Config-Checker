MAKE	= make -r -j8
EXES	= Checker.exe Auth.exe
INCLUDE	= lib.cpp

%.exe : %.cpp Makefile
	g++ $*.cpp $(INCLUDE) -o $*.exe

# Commands

default :
	$(MAKE) all

all :
	$(MAKE) $(EXES)
