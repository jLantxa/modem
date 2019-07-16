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
	AlsaAudioSinkTest \
	FourierTest

CircularBufferTest:
	$(CC) $(CFLAGS) -DDEBUG_LEVEL=6 -I $(INCLUDE)/ \
		$(TEST)/CircularBufferTest.cpp \
	-o $(OUT)/CircularBufferTest

AlsaAudioSinkTest:
	$(CC) $(CFLAGS) $(ALSA_LFLAGS) -DDEBUG_LEVEL=6 -I $(INCLUDE)/ \
		$(SRC)/NCO.cpp \
		$(SRC)/AlsaAudioSink.cpp \
		$(TEST)/AlsaAudioSinkTest.cpp \
	-o $(OUT)/AlsaAudioSinkTest

FourierTest:
	$(CC) $(CFLAGS) -DDEBUG_LEVEL=6 -I $(INCLUDE)/ \
		$(SRC)/fourier.cpp \
		$(TEST)/FourierTest.cpp \
	-o $(OUT)/FourierTest
