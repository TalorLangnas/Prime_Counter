CC = gcc
CFLAGS = -g -Wall -pthread
OBJ = primeCounter.o task.o queue_task.o producer.o worker.o algorithms.o 
TARGET = primeCounter 
GENERATOR_SRC = generator.c
GENERATOR_TARGET = randomGenerator


all: $(TARGET) $(GENERATOR_TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(GENERATOR_TARGET): $(GENERATOR_SRC)
	$(CC) -o $@ $< $(CFLAGS)

clean:
	rm -f $(OBJ) $(TARGET) $(GENERATOR_TARGET)

