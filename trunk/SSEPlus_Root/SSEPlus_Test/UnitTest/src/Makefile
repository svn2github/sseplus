##
## Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
## This software is subject to the Apache v2.0 License.
##
OBJS = main.o
SRCS = $(addsuffix .cpp, $(basename $(OBJS))) 
CXXFLAGS = -O2
EXE = ../UnitTest

all:	$(EXE) $(OBJS)

$(EXE): $(OBJS)
	$(CXX) -m$(BITNESS) -o $@ $(OBJS)

clean:
	rm -f $(EXE) $(OBJS)

.cpp.o:
	$(CXX) -DSYS$(BITNESS) -m$(BITNESS) $(CXXFLAGS) $(CP_FLAGS) -o $@ -c $<

depend:	$(SRCS)
	$(MAKEDEPEND) -Y $(SRCS)

# DO NOT DELETE

main.o: ../include/test.h ../../../SSEPlus/include/SSEPlus_platform.h
main.o: ../include/format.h ../../../SSEPlus/include/SSEPlus_base.h
main.o: ../../../SSEPlus/include/SSEPlus_platform.h
main.o: ../../../SSEPlus/include/logical/SSEPlus_logical_REF.h
main.o: ../../../SSEPlus/include/SSEPlus_base.h ../../../SSEPlus/include/SSEPlus.h
main.o: ../../../SSEPlus/include/SSEPlus_base.h ../../../SSEPlus/include/SSEPlus_REF.h
main.o: ../../../SSEPlus/include/number/SSEPlus_number_REF.h
main.o: ../../../SSEPlus/include/arithmetic/SSEPlus_arithmetic_REF.h
main.o: ../../../SSEPlus/include/SSEPlus_SSE2.h
main.o: ../../../SSEPlus/include/arithmetic/SSEPlus_arithmetic_SSE2.h
main.o: ../../../SSEPlus/include/logical/SSEPlus_logical_SSE2.h
main.o: ../../../SSEPlus/include/SSEPlus_SSE3.h
