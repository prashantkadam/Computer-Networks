/*--------------------------------------------------------------------*/
/* functions to connect clients and server */

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netdb.h>
#include <time.h> 
#include <errno.h>

#include <stdlib.h>

#define MAXNAMELEN 256
/*--------------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/* prepare server to accept requests
 returns file descriptor of socket
 returns -1 on error
 */
int startserver() {
	int sd; /* socket descriptor */

	char * servhost; /* full name of this host */
	ushort servport; /* port assigned to this server */
	int len;

	struct sockaddr_in server;
	/*
	 FILL HERE
	 create a TCP socket using socket()
	 */
	 if((sd = socket(AF_INET,SOCK_STREAM,0)) == -1){
	 	perror("socket()");
	 	exit(-1);
	 }

	server.sin_family = AF_INET;
	server.sin_port = htons(0);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero,8);
	len = sizeof(struct sockaddr_in);

	/*
	 FILL HERE
	 bind the socket to some port using bind()
	 let the system choose a port
	 */
	 if((bind(sd,(struct sockaddr *)&server,len)) == -1)
	 {
		perror("bind :");
		exit(-1);
	 }

	/* we are ready to receive connections */
	//listen(sd, 5);
	if(listen(sd,5) == -1)
	{
		perror("listen :");
		exit(-1);
	}

	/*
	 FILL HERE
	 figure out the full host name (servhost)
	 use gethostname() and gethostbyname()
	 full host name is remote**.cs.binghamton.edu
	 */
	// int len_hostname=128;
	 int gethostname_return = gethostname(&servhost,128);

	 if(gethostname_return == -1){
	 	perror("gethostname() : ");
	 	exit(-1);
	 }

	 struct hostent *tmp = 0;
	struct in_addr **addr_list;
	//printf("%s\n", "------------------");
	tmp = gethostbyname((const char *)&servhost);

	 if (!tmp) {
        printf("Lookup Failed:");
        return 0;
    }


	/*
	 FILL HERE
	 figure out the port assigned to this server (servport)
	 use getsockname()
	 */
	servhost = malloc(sizeof(tmp->h_length));
	 memcpy(servhost,tmp->h_name,strlen(tmp->h_name));
	 if(getsockname(sd,(struct sockaddr *)&server,&len) == -1){
	 	printf("%s\n", "-1 here");
	 	return -1;
	 }
	servport = server.sin_port;

	
	/* ready to accept requests */
	printf("admin: started server on '%s' at '%hu'\n", servhost, ntohs(servport));
		
	free(servhost);
	return (sd);
}
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
/*
 establishes connection with the server
 returns file descriptor of socket
 returns -1 on error
 */
int hooktoserver(char *servhost, ushort servport) {
	
	int sd; /* socket descriptor */

	ushort clientport; /* port assigned to this client */
	struct sockaddr_in server_address,client_addr;
	/*
	 FILL HERE
	 create a TCP socket using socket()
	 */
	 if((sd = socket(AF_INET,SOCK_STREAM,0)) == -1){
	 	perror("socket()");
	 	exit(-1);
	 }
	
	/*
	 FILL HERE
	 connect to the server on 'servhost' at 'servport'
	 use gethostbyname() and connect()
	 */
	 struct hostent *hostent_server = 0;
	 struct in_addr **server_addr_list;
	 hostent_server = gethostbyname(servhost);

	 if (!hostent_server) {
        printf("Lookup Failed:%s\n", hstrerror(h_errno));
        return 0;
    }

	server_address.sin_family = AF_INET;
  	server_address.sin_port = htons(servport);
  	server_address.sin_addr.s_addr = inet_addr(inet_ntoa( (struct in_addr) *((struct in_addr *) hostent_server->h_addr_list[0])));

  	if(connect(sd, (struct sockaddr *)&server_address, sizeof(server_address))<0)
    {
      printf("\n Error : Connect Failed \n");
      return 1;
    }

	/*
	 FILL HERE
	 figure out the port assigned to this client
	 use getsockname()
	 */
	 int len;
	 len  = sizeof(client_addr);
	 if(getsockname(sd,(struct sockaddr *)&client_addr,&len) == -1){
	 	printf("%s\n", "getsockname -1 here");
	 	return -1;
	 }
	clientport = ntohs(client_addr.sin_port);


	/* succesful. return socket descriptor */
	printf("admin: connected to server on '%s' at '%hu' thru '%hu'\n", servhost,
			servport, clientport);
	printf(">");
	fflush(stdout);
	return (sd);
}
/*----------------------------------------------------------------*/

/*----------------------------------------------------------------*/
int readn(int sd, char *buf, int n) {
	int toberead;
	char * ptr;

	toberead = n;
	ptr = buf;
	while (toberead > 0) {
		int byteread;

		byteread = read(sd, ptr, toberead);
		if (byteread <= 0) {
			if (byteread == -1)
				perror("read");
			return (0);
		}

		toberead -= byteread;
		ptr += byteread;
	}
	return (1);
}

char *recvtext(int sd) {
	char *msg;
	long len;

	/* read the message length */
	if (!readn(sd, (char *) &len, sizeof(len))) {
		return (NULL);
	}
	len = ntohl(len);

	/* allocate space for message text */
	msg = NULL;
	if (len > 0) {
		msg = (char *) malloc(len);
		if (!msg) {
			fprintf(stderr, "error : unable to malloc\n");
			return (NULL);
		}

		/* read the message text */
		if (!readn(sd, msg, len)) {
			free(msg);
			return (NULL);
		}
	}

	/* done reading */
	return (msg);
}

int sendtext(int sd, char *msg) {
	long len;

	/* write lent */
	len = (msg ? strlen(msg) + 1 : 0);
	len = htonl(len);
	write(sd, (char *) &len, sizeof(len));

	/* write message text */
	len = ntohl(len);
	if (len > 0)
		write(sd, msg, len);
	return (1);
}
/*----------------------------------------------------------------*/

