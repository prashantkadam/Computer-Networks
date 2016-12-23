/*--------------------------------------------------------------------*/
/* conference server */

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

extern char * recvtext(int sd);
extern int sendtext(int sd, char *msg);

extern int startserver();
/*--------------------------------------------------------------------*/

/*--------------------------------------------------------------------*/
int fd_isset(int fd, fd_set *fsp) {
	return FD_ISSET(fd, fsp);
}
/* main routine */
int main(int argc, char *argv[]) {
	int j,i;
	int servsock; /* server socket descriptor */
	int clientsd;
	fd_set livesdset,tempsdset; /* set of live client sockets */
	int livesdmax; /* largest live client socket descriptor */
	
	int bytes_read;
	struct sockaddr_in client_address;
	int len = sizeof (struct sockaddr_in);
	/* check usage */
	if (argc != 1) {
		fprintf(stderr, "usage : %s\n", argv[0]);
		exit(1);
	}

	/* get ready to receive requests */
	servsock = startserver();
	if (servsock == -1) {
		perror("Error on starting server: ");
		exit(1);
	}

	/*
	 FILL HERE:
	 init the set of live clients
	 */
	 FD_ZERO(&livesdset);
	 FD_ZERO(&tempsdset);
	 FD_SET(servsock,&livesdset);
	 livesdmax = servsock;

	/* receive requests and process them */
	while (1) {
		int frsock; /* loop variable */
		FD_ZERO(&tempsdset);
		tempsdset = livesdset;
		/*
		 FILL HERE
		 wait using select() for
		 messages from existing clients and
		 connect requests from new clients
		 */
		 if(select(livesdmax+1,&tempsdset,NULL,NULL,NULL) == -1){
			perror("Select():");
			exit(-1);
		}


		/* look for messages from live clients */
		for (frsock = 3; frsock <= livesdmax; frsock++) {
			/* skip the listen socket */
			/* this case is covered separately */
			if (frsock == servsock)
				continue;
			
			if(fd_isset(frsock,&tempsdset)/* FILL HERE: message from client 'frsock'? */){
				char *msg;
				char * clienthost; /* host name of the client */
				ushort clientport; /* port number of the client */
				socklen_t len;
				struct sockaddr_storage addr;
				//addr.sin_family = AF_INET;
				len = sizeof(struct sockaddr_in);
				char ipstr[20];
				/*
				 FILL HERE:
				 figure out client's host name and port
				 using getpeername() and gethostbyaddr()
				 */
				struct sockaddr_in *s;
				int port;
				 getpeername(frsock, (struct sockaddr*)&addr, &len);
				 if (addr.ss_family == AF_INET) {
					    s = (struct sockaddr_in *)&addr;
					    port = ntohs(s->sin_port);
					    inet_ntop(AF_INET, &s->sin_addr, ipstr, sizeof ipstr);


					    struct hostent *he;
						struct in_addr cliaddr;
						inet_pton(AF_INET, ipstr, &cliaddr);
						he = gethostbyaddr(&cliaddr, sizeof cliaddr, AF_INET);
						clienthost = he->h_name;
						clientport = port;
					} 

				struct hostent *tmphst;
				msg = recvtext(frsock);
				if( !msg){
					printf("admin: disconnect from '%s(%hu)'\n", clienthost,clientport);
					close(frsock);
                	FD_CLR(frsock, &livesdset);
				}
				else
				{
					printf("%s(%hu): %s", clienthost, clientport, msg);
					//send to all other
					for (j = 3; j <= livesdmax; j++) {
                    // send to everyone!
                    if (FD_ISSET(j, &livesdset)) {
                        // except the listener and ourselves
                        if (j != servsock && j != frsock) {
                        	//printf("%s\n", "In send");
                            if (sendtext(j,msg) == -1) {
                                perror("send");
                            }
                        }
                    }
                }
				}
		}
		}
			if(fd_isset(servsock,&tempsdset)){
							if(servsock == servsock){
								//printf("%s\n", "new request here");
						/*
						 FILL HERE:
						 accept a new connection request
						 */
						 int csd = accept(servsock,(struct sockaddr*) &client_address,&len);
						 if(csd == -1){
						 	perror("accept():");
						 	exit(-1);
						 }

						/* if accept is fine? */
						if (csd != -1) {
							char * clienthost; /* host name of the client */
							ushort clientport; /* port number of the client */
							
							if(csd>livesdmax){
								livesdmax = csd;
							}
							/*
							 FILL HERE:
							 figure out client's host name and port
							 using gethostbyaddr() and without using getpeername().
							 */
							 struct hostent *tmphst;
							 struct in_addr cliaddr = client_address.sin_addr;
							 tmphst = gethostbyaddr(&cliaddr,sizeof cliaddr,AF_INET);
							 clienthost = tmphst->h_name;
							 clientport = client_address.sin_port;

							printf("admin: connect from '%s' at '%hu'\n", clienthost,
									ntohs(clientport));

							/*
							 FILL HERE:
							 add this guy to set of live clients
							 */
							//printf("%s\n","set csd" );
							 FD_SET(csd,&livesdset);

						} else {
							perror("accept");
							exit(0);
						}
					}
				}
			//}
		}
		
	
	return 0;
}
/*--------------------------------------------------------------------*/

