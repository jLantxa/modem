CC=clang++
CFLAGS=-std=c++17

INCLUDE=include
SRC=src
OUT=build

init:
	mkdir -p $(OUT)

clean:
	rm -rf $(OUT)/*
