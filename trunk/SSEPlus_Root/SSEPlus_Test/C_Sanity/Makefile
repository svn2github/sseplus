##
## Copyright (c) 2006-2008 Advanced Micro Devices, Inc. All Rights Reserved.
## This software is subject to the Apache v2.0 License.
##
OBJS = main.o
SRCS = $(addsuffix .c, $(basename $(OBJS))) 
CCFLAGS = -O2
EXE = C_Sanity

all:	$(EXE) $(OBJS)

$(EXE): $(OBJS)
	$(CC) -m$(BITNESS) -o $@ $(OBJS) -lm

clean:
	rm -f $(EXE) $(OBJS)

.c.o:
	$(CC) -DSYS$(BITNESS) -m$(BITNESS) $(CCFLAGS) $(CP_FLAGS) -o $@ -c $<

depend:	$(SRCS)
	$(MAKEDEPEND) -Y $(SRCS)

# DO NOT DELETE

main.o: ../../SSEPlus/include/SSEPlus.h ../../SSEPlus/include/SSEPlus_base.h
main.o: ../../SSEPlus/include/SSEPlus_platform.h ../../SSEPlus/include/SSEPlus_REF.h
main.o: ../../SSEPlus/include/number/SSEPlus_number_REF.h
main.o: ../../SSEPlus/include/arithmetic/SSEPlus_arithmetic_REF.h
main.o: ../../SSEPlus/include/SSEPlus_SSE2.h
main.o: ../../SSEPlus/include/arithmetic/SSEPlus_arithmetic_SSE2.h
main.o: ../../SSEPlus/include/logical/SSEPlus_logical_SSE2.h
main.o: ../../SSEPlus/include/SSEPlus_SSE3.h ../../SSEPlus/include/SSEPlus_REF.h
