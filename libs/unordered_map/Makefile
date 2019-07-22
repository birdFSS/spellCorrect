SRCS:=$(wildcard *.cc)
CPP_OBJS:=$(patsubst %.cc,%.o,$(SRCS))
TARGET:=main.exe
CC:=g++
CFLAGS:= -g -Wall -lpthread
all:$(TARGET)
$(TARGET): $(CPP_OBJS)
	$(CC) $^ -o $@ $(CFLAGS)
%.o:%.cc
	$(CC) -c -o $@ $< $(CFLAGS)
.PHONY:clean
clean:
	rm $(TARGET)
