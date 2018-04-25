CC = g++
TARGET = main

$(TARGET): $(TARGET).o dijkstra.o
		$(CC) -o $(TARGET) $(TARGET).o dijkstra.o

$(TARGET).o: $(TARGET).cc
		$(CC) -c -o $(TARGET).o $(TARGET).cc

dijkstra.o: dijkstra.cc
		$(CC) -c -o dijkstra.o dijkstra.cc

clean:
	rm *.o $(TARGET)
