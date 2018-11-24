CC=gcc
CXX=g++
RM=rm -f

CPPFLAGS=-O3 -std=c++11 -pg 
LDFLAGS=-O3 -std=c++11 -pg
LDLIBS=

SRCS=ncs.cpp scheme.cpp blockfinder.cpp ncs_test.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
all: test_ncs


ncs.o: ncs.cpp ncs.h 
scheme.o: scheme.cpp scheme.h 
blockfinder.o: blockfinder.cpp blockfinder.h 

ncs_test.o: ncs_test.cpp ncs.h scheme.h blockfinder.h

test_ncs: $(OBJS)
	$(CXX) $(LDFLAGS) -o test_ncs $(OBJS) $(LDLIBS)

test:
	./test_ncs

clean:
	$(RM) $(OBJS) test_ncs
