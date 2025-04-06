CC		= clang
# Debug
CFLAGS	= -c -std=c11 -Wall -g3 -pthread
# Release
# CFLAGS	= -std=c11 -Wall -O3
LFLAGS	= -lm -lpthread
TARGET	= HW3
FILES	= main.o

all: $(FILES)
	$(CC) $^ -o $(TARGET) $(LFLAGS) 

$(FILES): %.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
	rm $(TARGET)

rebuild: clean all