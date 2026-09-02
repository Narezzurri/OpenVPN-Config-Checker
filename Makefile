VERSION		= 2.0.1
MAKE		= make -r
DEL			= del /s
COPY		= copy
EXES		= Checker.exe Auth.exe
INCLUDE		= lib.cpp
MAKENSIS	= makensis

default :
	$(MAKE) all -j8

# Specific rules

OpenVPNConfigManagerSetup-$(VERSION).exe : Setup.nsi Makefile

	$(MAKENSIS) -dVERSION=$(VERSION) Setup.nsi

# Commands

build :
	$(MAKE) -C Checker Checker.exe
	$(MAKE) -C Authenticator Auth.exe
	$(MAKE) OpenVPNConfigManagerSetup-$(VERSION).exe

all :
	$(MAKE) -C Checker Checker.exe
	$(MAKE) -C Authenticator Auth.exe

clean :
	$(DEL) *.exe
	$(DEL) *.ovpn
