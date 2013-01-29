CFLAGS := -I../
all: server client


server: server.c
	gcc -o server server.c $(CFLAGS)

client: client.c
	gcc -o client client.c $(CFLAGS)


clean:
	rm client &> /dev/null
	rm server &> /dev/null
