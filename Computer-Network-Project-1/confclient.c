/*--------------------------------------------------------------------*/
/* conference client */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netdb.h>
#include <time.h> 
#include <errno.h>

#include <stdlib.h>
#include "confutils.c"

#define MAXMSGLEN  1024

extern char * recvtext(int sd);
extern int sendtext(int sd, char *msg);

extern int hooktoserver(char *servhost, ushort servport);
/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
	int sock;
	int fd_maximum;
	fd_set rfds,tempsdset;
	int retval;

	/* check usage */
	if (argc != 3) {
		fprintf(stderr, "usage : %s <servhost> <servport>\n", argv[0]);
		exit(1);
	}

	/* get hooked on to the server */
	sock = hooktoserver(argv[1], atoi(argv[2]));
	if (sock == -1) {
		perror("Error: ");
		exit(1);
	}

	FD_ZERO(&rfds);
	FD_ZERO(&tempsdset);
	FD_SET(0, &rfds);
	FD_SET(sock, &rfds);
	//printf("sock -  %d\n", sock);
	fd_maximum = sock;
	/* keep talking */
	while (1) {
		FD_ZERO(&tempsdset);
		tempsdset = rfds;
		/*
		 FILL HERE
		 use select() to watch simultaneously for
		 inputs from user and messages from server
		 */
		 if(select(fd_maximum + 1 ,&tempsdset,NULL,NULL,NULL) == -1){
			perror("Select():");
			exit(-1);
		}

		if (FD_ISSET(sock,&tempsdset)/* FILL HERE: message from server? */) {
			//printf("%s\n", "msg from server");
			char *msg;
			msg = recvtext(sock);
			if (!msg) {
				/* server killed, exit */
				fprintf(stderr, "error: server died\n");
				exit(1);
			}

			/* display the message */
			printf(">>> %s", msg);
			/* free the message */
			free(msg);
		}

		if (FD_ISSET(0,&tempsdset)/* FILL HERE: input from keyboard? */) {
			//printf("%s\n", "msg from std in");
			char msg[MAXMSGLEN];
			if (!fgets(msg, MAXMSGLEN, stdin))
				exit(0);
			sendtext(sock, msg);
		}

		printf(">");
		fflush(stdout);
	}
	return 0;
}
/*--------------------------------------------------------------------*/

