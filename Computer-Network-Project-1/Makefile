# compile client and server
all: confclient confserver

# compile client only
confclient: confclient.c
	gcc -g -o confclient confclient.c

# compile server program
confserver: confserver.c
	gcc -g -o confserver confserver.c

clean:
	rm -f *.o confclient confserver
