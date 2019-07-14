CC=clang++
CFLAGS=-std=c++17

INCLUDE=include
SRC=src
TEST=test
OUT=build

init:
	@mkdir -p $(OUT)

clean:
	@rm -rf $(OUT)/*

tests:
	@make CircularBufferTest

CircularBufferTest:
	$(CC) $(CFLAGS) -I $(INCLUDE)/ \
	$(TEST)/CircularBufferTest.cpp \
	-o $(OUT)/CircularBufferTest
