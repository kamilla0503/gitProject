CC=gcc
CXX=g++
RM=rm -f

CPPFLAGS=-g 
LDFLAGS=-g 
LDLIBS=

SRCS=ncs.cpp ncs_test.cpp ELBcpp.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: test_ncs

ncs.o: ncs.cpp ncs.h

ncs_test.o: ncs_test.cpp ncs.h

ELBcp.o: ELBcpp.cpp ncs.h

test_ncs: $(OBJS)
	$(CXX) $(LDFLAGS) -o test_ncs $(OBJS) $(LDLIBS)

test:
	./test_ncs

clean:
	$(RM) $(OBJS) test_ncs
