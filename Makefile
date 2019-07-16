CC=clang++
CFLAGS=-std=c++17 -Werror -O3

INCLUDE=include
SRC=src
TEST=test
OUT=build

ALSA_LFLAGS=-lasound

init:
	@mkdir -p $(OUT)

clean:
	@rm -rf $(OUT)/*

count-lines:
	cloc $(SRC)/ $(INCLUDE)/ $(TEST)/

# TESTS #
tests: \
	CircularBufferTest \
	OscillatorTest \
	AlsaAudioSinkTest

CircularBufferTest:
	$(CC) $(CFLAGS) -DDEBUG_LEVEL=6 -I $(INCLUDE)/ \
		$(TEST)/CircularBufferTest.cpp \
	-o $(OUT)/CircularBufferTest

OscillatorTest:
	$(CC) $(CFLAGS) -DDEBUG_LEVEL=6 -I $(INCLUDE)/ \
		$(SRC)/Oscillator.cpp \
		$(TEST)/OscillatorTest.cpp \
	-o $(OUT)/OscillatorTest

AlsaAudioSinkTest:
	$(CC) $(CFLAGS) $(ALSA_LFLAGS) -DDEBUG_LEVEL=6 -I $(INCLUDE)/ \
		$(SRC)/Oscillator.cpp \
		$(SRC)/AlsaAudioSink.cpp \
		$(TEST)/AlsaAudioSinkTest.cpp \
	-o $(OUT)/AlsaAudioSinkTest
