#
# Makefile.am for libstorage/testsuite
#

SUBDIRS = lib config libstorage.test single.out
PACKAGE = libstorage
AUTOMAKE_OPTIONS = dejagnu

INCLUDES = -I$(top_srcdir)/libstorage/src

AM_CPPFLAGS =
AM_CXXFLAGS =

noinst_PROGRAMS = partition1.single

partition1_single_SOURCES = partition1.cc
partition1_single_LDADD = ../src/liby2storage.la

clean-local:
	rm -f tmp.err.* tmp.out.* site.exp site.bak

EXTRA_DIST = disk_hda disk_hdb
