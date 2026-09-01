MAKE	= make -r
DEL		= del
EXES	= Checker.exe Auth.exe
INCLUDE	= lib.cpp

%.exe : %.cpp Makefile
	g++ $*.cpp $(INCLUDE) -o $*.exe -g

# Commands

default :
	$(MAKE) all -j8

all :
	$(MAKE) $(EXES)

clean :
	$(DEL) *.exe
	$(DEL) *.ovpn
