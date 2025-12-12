#authors: Jesus José Santamaría Santos(j.j.ssantos@udc.es), José Comerón Lado(jose.comeronl@udc.es)
#date: October 2025

CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -g
LDFLAGS = 

TARGET = p3

SOURCES = vars.c p3.c auxiliar.c commands.c historic_list.c file_list.c mem_list.c background_list.c
HEADERS = macros.h types.h auxiliar.h commands.h historic_list.h file_list.h mem_list.h background_list.h
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

%.o: %.c $(HEADERS)
	$(CC) ${CFLAGS} -c $< -o $@

valgrind: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)