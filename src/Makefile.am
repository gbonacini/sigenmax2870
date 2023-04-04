lib_LTLIBRARIES = libsigenmax2870.la libparsecmdline.la
libsigenmax2870_la_SOURCES = sigenmax2870_utils.cpp checkendianess.cpp
libsigenmax2870_la_LDFLAGS = -version-info 1:0:0
libsigenmax2870_la_CPPFLAGS  = -I../include

libparsecmdline_la_SOURCES = parseCmdLine.cpp 
libparsecmdline_la_LDFLAGS = -version-info 1:0:0
libparsecmdline_la_CPPFLAGS  = -I../include

bin_PROGRAMS   = sigenmax2870
dist_man_MANS  = ../doc/sigenmax2870.1

nobase_include_HEADERS   = ../include/sigenmax2870.hpp ../include/parseCmdLine.hpp ../include/safeconversion.hpp ../include/checkendianess.hpp
sigenmax2870_SOURCES     = sigenmax2870.cpp 
sigenmax2870_LDADD       = libsigenmax2870.la libparsecmdline.la

ACLOCAL_AMFLAGS = -I m4

