#This is an easier to use and modify makefile, but it is slightly more difficult to read than the simple one:

#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = gcc
CPP = g++
PLATFORM = $(shell uname -s)
ROOTDIR = $(shell pwd)
SOCKLIBPATH = /root/LapiMyProg/SocketProg/SocketLibrary
# define any compile-time flags
CFLAGS = -std=c++11 -Wall -g

# define any directories containing header files other than /usr/include
#
INCLUDES = -I$(ROOTDIR)/include/ \
						-I$(SOCKLIBPATH)/common/include \
						-I$(SOCKLIBPATH)/logging/include \
						-I$(SOCKLIBPATH)/tcpSocket/include
						
# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -L$(SOCKLIBPATH)/common \
					-L$(SOCKLIBPATH)/logging \
					-L$(SOCKLIBPATH)/tcpSocket 

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
#LIBS = -lm
LIBS = -llogger -lcommon -ltcpconnect

# define the C source files
SRCDIR = $(ROOTDIR)/source
SRCS = $(SRCDIR)/server.cpp 

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
TARGET = $(shell mkdir -p $(ROOTDIR)/$(PLATFORM))
OBJS = $(SRCS:.c=.o)
OBJSCPP = $(SRCS:.cpp=.o)

# define the executable file 
MAIN = server

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean


all:    $(MAIN)
	@echo  Simple compiler named main has been compiled
	@echo  Platform is $(PLATFORM)  

$(MAIN): $(OBJS) 
	$(TARGET)
	$(CPP) $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS) -o $(ROOTDIR)/$(PLATFORM)/$(MAIN) $(OBJS) 


# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CPP) $(CFLAGS) $(INCLUDES) $(LFLAGS) $(LIBS) -c $<  -o $@
clean:
	$(RM) $(SRCDIR)/*.o *~ $(ROOTDIR)/$(PLATFORM)/$(MAIN) 
	$(RM) -r $(ROOTDIR)/$(PLATFORM)

depend: $(SRCS)
	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it

