VERSION		= 2.0.1
MAKE		= make -r
DEL			= del
EXES		= Checker.exe Auth.exe
INCLUDE		= lib.cpp
MAKENSIS	= makensis

default :
	$(MAKE) all -j8

# Specific rules

OpenVPNConfigManagerSetup-$(VERSION).exe : $(EXES) Setup.nsi Makefile

	$(MAKENSIS) -dVERSION=$(VERSION) Setup.nsi

# General rules

%.exe : %.cpp %Help.txt Makefile
	g++ $*.cpp $(INCLUDE) -o $*.exe -g

# Commands

build :
	$(MAKE) OpenVPNConfigManagerSetup-$(VERSION).exe

all :
	$(MAKE) $(EXES)

clean :
	$(DEL) *.exe
	$(DEL) *.ovpn
