CC=clang++
CFLAGS=-std=c++17

INCLUDE=include
SRC=src
TEST=test
OUT=build

ALSA_LFLAGS=-lasound

init:
	@mkdir -p $(OUT)

clean:
	@rm -rf $(OUT)/*

tests:
	make CircularBufferTest
	make AlsaAudioSinkTest

CircularBufferTest:
	$(CC) $(CFLAGS) -I $(INCLUDE)/ \
		$(TEST)/CircularBufferTest.cpp \
	-o $(OUT)/CircularBufferTest

AlsaAudioSinkTest:
	$(CC) $(CFLAGS) $(ALSA_LFLAGS) -I $(INCLUDE)/ \
		$(SRC)/AlsaAudioSink.cpp \
		$(TEST)/AlsaAudioSinkTest.cpp \
	-o $(OUT)/AlsaAudioSinkTest
