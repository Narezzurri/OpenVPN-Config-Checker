MAKE		= make -r
DEL			= del
OBJ			= Auth.exe
INCLUDE		= ../lib.cpp

default :
	$(MAKE) all -j8

# General rules

%.exe : %.cpp %Help.txt Makefile
	g++ $*.cpp resource.rc $(INCLUDE) -o $*.exe -g -I ..

# Commands

all :
	$(MAKE) $(OBJ)

clean :
	$(DEL) *.exe
	$(DEL) *.ovpn
