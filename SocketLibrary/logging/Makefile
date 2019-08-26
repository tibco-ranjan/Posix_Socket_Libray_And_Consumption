# Makefile template for shared library

CC = gcc # C compiler
CPP = g++ #CPP compiler
CFLAGS = -fPIC -Wall -Wextra  -g # C flags
LDFLAGS = -shared  # linking flags
RM = rm -f  # rm command
ROOTDIR = /root/LapiMyProg/SocketProg/SocketLibrary
CURRENTDIR = $(shell pwd)
INCLUDES = -I$(ROOTDIR)/common/include/ \
						-I$(CURRENTDIR)/include
					
TARGET_LIB = liblogger.so # target lib
SRCDIR = $(CURRENTDIR)/source
SRCS = $(SRCDIR)/CLogger.cpp \
			$(SRCDIR)/CLoggerException.cpp

OBJS = $(SRCS:.c=.o)
OBJSCPP = $(SRCS:.cpp=.o)

.PHONY: all
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJSCPP)
	$(CPP) ${LDFLAGS} -o $@ $^

.cpp.o:
	$(CPP) $(CFLAGS) $(INCLUDES) -c $<  -o $@

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJSCPP} 

