##
## Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
## This software is subject to the Apache v2.0 License.
##
SUBDIRS = C_Sanity UnitTest 

all:
	@for i in $(SUBDIRS); do (cd $$i; $(MAKE) all); done

clean:
	@for i in $(SUBDIRS); do (cd $$i; $(MAKE) clean); done

