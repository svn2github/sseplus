##
## Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
## This software is subject to the Apache v2.0 License.
##
SHELL = /bin/bash
MAKE = /usr/bin/make

CC = gcc
CXX = g++
MAKEDEPEND = makedepend

SUBDIRS = SSEPlus_Test

MAKEFLAGS = MAKE=$(MAKE) CC=$(CC) CXX=$(CXX) MAKEDEPEND=$(MAKEDEPEND) CXXFLAGS_CP=$(CXXFLAGS_CP)

all:
	@for i in $(SUBDIRS); do (cd $$i; $(MAKE) all); done

clean:
	@for i in $(SUBDIRS); do (cd $$i; $(MAKE) clean); done
 
# DO NOT DELETE
