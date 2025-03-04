CC = gcc
CC_FLAGS = -Wall

all: run

run: main.o server.o handleclient.o closeserver.o consumer.o
	$(CC) $(CC_FLAGS) -o main main.o server.o handleclient.o closeserver.o consumer.o

main.o: main.c
	$(CC) $(CC_FLAGS) -c main.c

server.o: server.c
	$(CC) $(CC_FLAGS) -c server.c

handleclient.o: handleclient.c
	$(CC) $(CC_FLAGS) -c handleclient.c

closeserver.o: closeserver.c
	$(CC) $(CC_FLAGS) -c closeserver.c

consumer.o: consumer.c
	$(CC) $(CC_FLAGS) -c consumer.c

clean:
	rm -f *.o main