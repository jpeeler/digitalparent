## Process this file with automake to produce Makefile.in

## Created by Anjuta - will be overwritten
## If you don't want it to overwrite it,
## 	Please disable it in the Anjuta project configuration

INCLUDES =\
	$(PACKAGE_CFLAGS)\
	 -I/Projects/DigitalParent/include

AM_CFLAGS =\
	 -Wall\
	 -g

AM_CXXFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = digitalparent

digitalparent_SOURCES = \
	controller.cc\
	data_structure.cc\
	database.cc\
	dbTestStub.cc

digitalparent_LDFLAGS = 

digitalparent_LDADD = \
	$(PACKAGE_LIBS)\
	 /usr/lib/libtntdb.la

