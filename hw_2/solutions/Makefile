CC = g++ -std=c++17
GTEST_DIR = /opt/homebrew/Cellar/googletest/1.15.2

CFLAGS = -g -I$(GTEST_DIR)/include
LIBS = -L$(GTEST_DIR)/lib -lgtest -lgtest_main -pthread

SRCS = solutions.c unit_tests.c main.c
OBJS = $(SRCS:.c=.o)
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

%.o: %.c solutions.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
