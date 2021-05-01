CC=clang++
CFLAGS=-std=c++20 -Wall -Werror -O2

INCLUDE=include
SRC=src
TEST=test
OUT=build

ALSA_LFLAGS=-lasound

init:
	@mkdir -p $(OUT)

clean:
	@rm -r ./$(OUT)

count-lines:
	cloc $(SRC)/ $(INCLUDE)/ $(TEST)/

ToneGenerator:
	$(CC) $(CFLAGS) $(ALSA_LFLAGS) -DDEBUG_LEVEL=6 -I $(INCLUDE)/ \
		$(SRC)/oscillator.cpp \
		$(SRC)/AlsaAudioSink.cpp \
		$(TEST)/ToneGenerator.cpp \
	-o $(OUT)/ToneGenerator