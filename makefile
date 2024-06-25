CC = gcc
CFLAGS = -g -Wall -pthread
OBJ = myPrimeCounter.o task.o queue_task.o producer.o worker.o algorithms.o
TARGET = myPrimeCounter

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(OBJ) $(TARGET)

