**************************************************************************************************************
					Project 1 : CS528 / Computer Network 
**************************************************************************************************************
Name  : Prashant Kadam
Email : pkadam1@binghamton.edu
**************************************************************************************************************
Implementation Details :
Given templates has three file , so project implementaion goes in three .c file 
1)confserver.c - code excuted on server
2)confclient.c -  code excuted on client
3)confutils.c - few helper methods for server anc client code

1) confserver.c
		- calls start server method from clientutil.c 
			in start server method -
				-create a TCP socket using socket()
				- bind the socket to some port (using INADDR_ANY ) using bind() 
				- Socket calls listen system call to listen for connection
		- executes a while to receive requests and process them, this loop is onlgoing , will break only when server dies..
		     -in while loop wait using select() for messages from existing clients and connect requests from new clients
		     - one for loop which will check for fdset from 3 to new max fd set ( 0 , 1 and 2 are reserved - stdin, stdout and stderr)
		     	- skip the listen socket (socket at server side)
		     	- check for recent activity using fd_isset , if old set fd then its a new message / disconnect request
		     		- if message then send that message to other connected client except the one who is sending . here using sendtext method in client utils
					- if disconnect then (i.e. msg is NULL) then reset fd for this connection
		     	- if activity for fd which is not set then its a new connection request
		     		accept new connection using accept system call, and add this to fdset and update max fd
2) confclient.c
		- call hooktoserver method from clientutill.c
				- this method creates a TCP socket using socket()
				- connect to the server on 'servhost' at 'servport' using gethostbyname() and connect()
		- one running  while loop 
				- this while loop uses  select() to watch simultaneously for inputs from user and messages from server
				- check recent activity on serpective fd activity can be message from server / server died notification
				- if message from server print message if message is NULL then server died ., display and exit

				- write messge using STDIN (input from keyboard) , then send message to server using sendtext clientutil method.
3) confutil.c 
		- follwoing method 
			- startserver()
			- hooktoserver()
			- recvtext() - already provided in template
			- sendtext() -  already provided in template

---------------------------------------------------------------------------------------------------------------------
steps to run Program -
	Server : 
			./confserver

	Client : 
			./confclient <servername> <port>
			example :- ./confclient remote00.cs.binghamton.edu 46050
---------------------------------------------------------------------------------------------------------------------
								*******************************************************			
												Sample Input / Output :
								*******************************************************			
---------------------------------------------------------------------------------------------------------------------
									server :- (remote00.cs.binghamton.edu):-
---------------------------------------------------------------------------------------------------------------------
remote00:~/pkadam1-project1> ./confserver

admin: started server on 'remote00.cs.binghamton.edu' at '54492'
admin: connect from 'remote03.cs.binghamton.edu' at '54052'
admin: connect from 'remote04.cs.binghamton.edu' at '57127'
remote04.cs.binghamton.edu(57127): hello from remote 04
remote03.cs.binghamton.edu(54052): hello from remote 03
remote04.cs.binghamton.edu(57127): good morning from remote 03
remote03.cs.binghamton.edu(54052): good morning from remote 03
remote04.cs.binghamton.edu(57127): bye from remote 04
remote03.cs.binghamton.edu(54052): bye from remote 03
admin: disconnect from 'remote04.cs.binghamton.edu(57127)'
admin: disconnect from 'remote03.cs.binghamton.edu(54052)'
^C
remote00:~/pkadam1-project1>
---------------------------------------------------------------------------------------------------------------------
									client 1 - (remote03.cs.binghamton.edu):-
---------------------------------------------------------------------------------------------------------------------
remote03:~/pkadam1-project1> ./confclient remote00.cs.binghamton.edu  54492  
admin: connected to server on 'remote00.cs.binghamton.edu' at '54492' thru '54052'
>>>> hello from remote 04
>hello from remote 03
>>>> good morning from remote 04
>good morning from remote 03
>>>> bye from remote 04
>bye from remote 03
>remote03:~/pkadam1-project1>


---------------------------------------------------------------------------------------------------------------------
									client 2 - (remote04.cs.binghamton.edu):-
---------------------------------------------------------------------------------------------------------------------
remote04:~/pkadam1-project1> ./confclient remote00.cs.binghamton.edu  54492
admin: connected to server on 'remote00.cs.binghamton.edu' at '54492' thru '57127'
>hello from remote 04
>>>> hello from remote 03
>good morning from remote 04
>>>> good morning from remote 03
>bye from remote 04
>>>> bye from remote 03
>remote04:~/pkadam1-project1>

**************************************************************************************************************
