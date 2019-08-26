# Makefile template for shared library

CC = gcc # C compiler
CPP = g++ #CPP compiler
CFLAGS = -fPIC -Wall -Wextra  -g # C flags
LDFLAGS = -shared # linking flags

ROOTDIR = /root/LapiMyProg/SocketProg/SocketLibrary
CURRENTDIR = $(shell pwd)
LFLAGS = -L$(ROOTDIR)/common -L$(ROOTDIR)/logging  -L/usr/lib/

RM = rm -f  # rm command
INCLUDES = -I$(ROOTDIR)/common/include/ \
						-I$(ROOTDIR)/logging/include/ \
						-I$(CURRENTDIR)/include
					
SRCDIR = $(CURRENTDIR)/source
SRCS = $(SRCDIR)/inet_socket.cpp \
				$(SRCDIR)/inet_accept.cpp \
				$(SRCDIR)/inet_handle_multiplex_io.cpp \
				$(SRCDIR)/readLine.cpp

OBJS = $(SRCS:.c=.o)
OBJSCPP = $(SRCS:.cpp=.o)
LIBS = -llogger

TARGET_LIB = libtcpconnect.so # target lib

.PHONY: all
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJSCPP)
	$(CPP) ${LDFLAGS} -o $@ $^

.cpp.o:
	$(CPP) $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS) -c $<  -o $@

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJSCPP} 

