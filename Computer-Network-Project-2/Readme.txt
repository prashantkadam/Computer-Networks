**************************************************************************************************************
									Project 2 : CS528 / Computer Network 
**************************************************************************************************************

Name  : Prashant Kadam
Email : pkadam1@binghamton.edu

**************************************************************************************************************
Implementation Details :
	Enitre code goes to dissector.c

	following is the important callback method which does all work of dissector
				got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
	above method is actually a callback method which repeatedely gets called for all packets
	step 1 : to calculate time since first captured packet using 
				subtract(...) method from libpcap_sniffex.h is used to acheive this

	step 2: print source MAC addr, destination MAC addr in hex format using 
				this is done using print_wlan_addr(..) methos from libpcap_sniffex.h
				to decide source and destination address, to_ds and from_ds flag i.e bit no 8 and 7 is used. from wlan_flag field
	step 3: for TCP : print source IP addr, source TCP port, destination IP addr, destination TCP port, IP length		
	step 4: for UDP : print source IP addr, source TCP port, destination IP addr, destination TCP port, IP length
		step 3 and 4 are acheived using simple print stmt of respective field and usnig inet_ntoa, ntohs etc as required.


---------------------------------------------------------------------------------------------------------------------

steps to run Program -
		./dissector sample1.pcap
		./dissector sample2.pcap

---------------------------------------------------------------------------------------------------------------------
								*******************************************************			
												Sample Input / Output :
								*******************************************************	
---------------------------------------------------------------------------------------------------------------------


./dissector sample1.pcap
0.000000  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:74.125.211.85  S_PORT:80  D_IP:10.0.2.4  D_PORT:49186  IP_LEN:1500
0.001628  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:74.125.211.85  S_PORT:80  D_IP:10.0.2.4  D_PORT:49186  IP_LEN:1500
0.001957  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:74.125.211.85  S_PORT:80  D_IP:10.0.2.4  D_PORT:49186  IP_LEN:1500
0.002228  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:74.125.211.85  S_PORT:80  D_IP:10.0.2.4  D_PORT:49186  IP_LEN:1500
0.002436  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:49186  D_IP:74.125.211.85  D_PORT:80  IP_LEN:52
0.002766  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:49186  D_IP:74.125.211.85  D_PORT:80  IP_LEN:52
0.003152  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:74.125.211.85  S_PORT:80  D_IP:10.0.2.4  D_PORT:49186  IP_LEN:1500
0.010957  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:74.125.211.85  S_PORT:80  D_IP:10.0.2.4  D_PORT:49186  IP_LEN:1500
0.011393  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:74.125.211.85  S_PORT:80  D_IP:10.0.2.4  D_PORT:49186  IP_LEN:1500
0.011840  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:74.125.211.85  S_PORT:80  D_IP:10.0.2.4  D_PORT:49186  IP_LEN:1500
0.012226  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:74.125.211.85  S_PORT:80  D_IP:10.0.2.4  D_PORT:49186  IP_LEN:1500
0.012682  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:74.125.211.85  S_PORT:80  D_IP:10.0.2.4  D_PORT:49186  IP_LEN:1500
0.016858  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:74.125.211.85  S_PORT:80  D_IP:10.0.2.4  D_PORT:49186  IP_LEN:1500
0.017158  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:74.125.211.85  S_PORT:80  D_IP:10.0.2.4  D_PORT:49186  IP_LEN:1500
0.019115  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:74.125.211.85  S_PORT:80  D_IP:10.0.2.4  D_PORT:49186  IP_LEN:1500	


./dissector sample2.pcap
0.000000  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:98.180.194.181  D_PORT:1377  IP_LEN:60
0.000445  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:108.28.91.252  D_PORT:80  IP_LEN:60
0.007930  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:216.75.224.178  D_PORT:80  IP_LEN:101
0.010410  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:216.75.224.178  S_PORT:80  D_IP:10.0.2.4  D_PORT:80  IP_LEN:101
0.024437  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:76.16.10.134  S_PORT:80  D_IP:10.0.2.4  D_PORT:80  IP_LEN:101
0.026925  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:76.16.10.134  D_PORT:80  IP_LEN:60
0.027304  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:216.75.224.178  D_PORT:80  IP_LEN:60
0.028286  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:76.16.10.134  D_PORT:80  IP_LEN:101
0.042915  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:98.180.194.181  S_PORT:1377  D_IP:10.0.2.4  D_PORT:80  IP_LEN:101
0.047733  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:98.180.194.181  D_PORT:1377  IP_LEN:60
0.052017  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:98.180.194.181  D_PORT:1377  IP_LEN:101
0.072296  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:98.83.185.34  D_PORT:50399  IP_LEN:1308
0.073052  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:98.83.185.34  D_PORT:50399  IP_LEN:1308
0.075294  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:98.180.194.181  D_PORT:1377  IP_LEN:101
0.078110  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:108.28.91.252  D_PORT:80  IP_LEN:102
0.078594  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:88.179.54.249  D_PORT:80  IP_LEN:84
0.084461  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:76.16.10.134  S_PORT:80  D_IP:10.0.2.4  D_PORT:80  IP_LEN:60
0.093533  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:98.83.185.34  S_PORT:50399  D_IP:10.0.2.4  D_PORT:80  IP_LEN:60
0.097775  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:216.75.224.178  S_PORT:80  D_IP:10.0.2.4  D_PORT:80  IP_LEN:60
0.101620  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:76.16.10.134  D_PORT:80  IP_LEN:102
0.102223  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:93.39.55.239  D_PORT:51115  IP_LEN:84
0.112153  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:108.28.91.252  S_PORT:80  D_IP:10.0.2.4  D_PORT:80  IP_LEN:101
0.119883  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:108.28.91.252  D_PORT:80  IP_LEN:60
0.121878  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:98.180.194.181  S_PORT:1377  D_IP:10.0.2.4  D_PORT:80  IP_LEN:60
0.125782  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:76.88.127.58  D_PORT:80  IP_LEN:102
0.126442  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:221.127.162.22  D_PORT:80  IP_LEN:84
0.129061  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:98.180.194.181  S_PORT:1377  D_IP:10.0.2.4  D_PORT:80  IP_LEN:85
0.147420  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:98.180.194.181  S_PORT:1377  D_IP:10.0.2.4  D_PORT:80  IP_LEN:60
0.147860  SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:98.180.194.181  D_PORT:1377  IP_LEN:60
0.149733  SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:98.180.194.181  S_PORT:1377  D_IP:10.0.2.4  D_PORT:80  IP_LEN:85



-----------------------------------------------------------------------------------------------------------------------------
