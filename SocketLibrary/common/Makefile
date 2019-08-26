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
TARGET_LIB = libcommon.so # target lib

SRCDIR = $(CURRENTDIR)/source
SRCS = $(SRCDIR)/get_num.c \
				$(SRCDIR)/error_functions.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

.PHONY: clean
clean:
	-${RM} ${TARGET_LIB} ${OBJS} 

