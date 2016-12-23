#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <sys/stat.h>

#include "libpcap_sniffex.h"

/*
 * dissect/print packet
 */
 //helper method to check binary number (in reverse order)
 void
 print_binary(int n){
 	while (n) {
    if (n & 1)
        printf("1");
    else
        printf("0");

    n >>= 1;
}
printf("\n");
 }

 void
got_packet2(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
	//printf("test: %d\n", args[1]);
	
	 struct pcap_pkthdr * end_header;
    end_header = (struct pcap_pkthdr*)*((u_char **)args);
    printf("%ld.%06ld  ", header->ts.tv_sec, header->ts.tv_usec);
    printf("\n");
    printf("%ld.%06ld  ", end_header->ts.tv_sec, end_header->ts.tv_usec);
    

}
 void
got_packet3(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
	const struct sniff_wlan *wlan;          /* 802.11 header  */
    //const struct sniff_ip *ip;              /* The IP header  */
    //const struct sniff_udp *udp;		    /* The UDP header */
    //const struct sniff_tcp *tcp;            /* The TCP header */

    //int size_ip;
    //int layer2_size = 0;

    /* define wlan header */
    wlan = (struct sniff_wlan*)(packet + SIZE_AVS);
    const u_char* source;
    const u_char* destination;

    /*
      FILL HERE
      print source MAC addr, destination MAC addr in hex format using 
      void print_wlan_addr(const u_char*) provided in libpcap_sniffex.h
      NOTE: You need to analyze the wlan header to figure out which address field is source addr, which is dest addr
    */
  // 	printf("%u\n", wlan->wlan_flags);

   //  print_binary(wlan->wlan_flags);
      //printf("%d\n",sizeof (wlan->wlan_flags) );
    //printf("%x\n",wlan->wlan_flags );
    int DS_to = (wlan->wlan_flags & 128);
    int DS_from = (wlan->wlan_flags & 64);

    if(DS_to == 0 && DS_from == 0){
    		source = wlan->wlan_addr2;
			destination = wlan->wlan_addr1;
    }
    if(DS_to == 0 && DS_from == 64){
    	source = wlan->wlan_addr2;
			destination = wlan->wlan_addr3;
    }
    if(DS_to == 128 && DS_from == 0){
    	source = wlan->wlan_addr3;
			destination = wlan->wlan_addr1;
    }
    if(DS_to == 128 && DS_from == 64){
    		source = wlan->wlan_addr3;
			destination = wlan->wlan_addr3;
    }
    printf("%d\n", DS_to);
    printf("%d\n", DS_from);
    source = wlan->wlan_addr2;
	destination = wlan->wlan_addr1;
	 printf("SA:");
	print_wlan_addr(source);
	printf("DA:");
	print_wlan_addr(destination);
	}

void
got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{	 
	/*
      FILL HERE
      calculate time since first captured packet using 
      struct timeval subtract(const struct timeval*, const struct timeval*)
      provided in libpcap_sniffex.h
    */
	struct timeval s_time;
	struct timeval e_time; 
	struct timeval tm_from_capture;
    s_time = header->ts;
    struct pcap_pkthdr * end_header;
    end_header = (struct pcap_pkthdr*)*((u_char **)args);
    //
    //static int count = 1;
    if(end_header->ts.tv_sec == 0 && end_header->ts.tv_usec == 0){
    //if(count == 1){
    	//printf("%s\n", "------------------------------");
    	end_header->ts.tv_sec = header->ts.tv_sec;
    	end_header->ts.tv_usec = header->ts.tv_usec;
    }
    //count++;
    e_time = end_header->ts;
    tm_from_capture = subtract(&s_time,&e_time);

    /* print time since first captured packet */
    printf("%ld.%06ld  ", tm_from_capture.tv_sec, tm_from_capture.tv_usec);

    /* declare pointers to packet headers */
    /* declare pointers to packet headers */
    const struct sniff_wlan *wlan;          /* 802.11 header  */
    const struct sniff_ip *ip;              /* The IP header  */
    const struct sniff_udp *udp;            /* The UDP header */
    const struct sniff_tcp *tcp;            /* The TCP header */

     int size_ip;
    int layer2_size = 0;

    /* define wlan header */
    wlan = (struct sniff_wlan*)(packet + SIZE_AVS);
    const u_char* source;
    const u_char* destination;

    /*
      FILL HERE
      print source MAC addr, destination MAC addr in hex format using 
      void print_wlan_addr(const u_char*) provided in libpcap_sniffex.h
      NOTE: You need to analyze the wlan header to figure out which address field is source addr, which is dest addr
    */
  // printf("%u\n", wlan->wlan_flags);

   //  print_binary(wlan->wlan_flags);
    
    int DS_to = (wlan->wlan_flags & 128);
    int DS_from = (wlan->wlan_flags & 64);

    if(DS_to == 0 && DS_from == 0){
    		source = wlan->wlan_addr2;
			destination = wlan->wlan_addr1;
    }
    if(DS_to == 0 && DS_from == 64){
    	source = wlan->wlan_addr2;
			destination = wlan->wlan_addr3;
    }
    if(DS_to == 128 && DS_from == 0){
    	source = wlan->wlan_addr3;
			destination = wlan->wlan_addr1;
    }
    if(DS_to == 128 && DS_from == 64){
    		source = wlan->wlan_addr3;
			destination = wlan->wlan_addr3;
    }

	
	//Print SA and DA like this SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43 
    printf("SA:");
	print_wlan_addr(source);
	printf("DA:");
	print_wlan_addr(destination);

    
	layer2_size = SIZE_AVS + SIZE_WLAN + SIZE_WLAN_LLC;

    /* this is to address the issue when subtype version is 8, 8 is actually a
     * reserved subtype, it seems to have 802.11e */
    if (WLAN_SUBTYPE(wlan) == 8)
	    layer2_size = layer2_size + 2;

    /* define/compute ip header offset */
    ip = (struct sniff_ip*)(packet + layer2_size);
    size_ip = IP_HL(ip)*4;
    if (size_ip < 20) {
        printf("   * Invalid IP header length: %u bytes\n", size_ip);
        return;
    }

	/* determine protocol */
    switch(ip->ip_p) {
        case IPPROTO_TCP:
            /*
              FILL HERE
              print source IP addr, source TCP port, destination IP addr, destination TCP port, IP length
              e.g., SA:00:1b:63:00:63:43  DA:00:25:bc:4c:8a:de  S_IP:74.125.211.85  S_PORT:80  D_IP:10.0.2.4  D_PORT:49186  IP_LEN:1500 
            */
            tcp = (struct sniff_tcp*)(packet+layer2_size+size_ip);
            printf("S_IP:%s  S_PORT:%d  ", inet_ntoa(ip->ip_src),ntohs(tcp->th_sport));			
			printf("D_IP:%s  D_PORT:%d  IP_LEN:%d\n", inet_ntoa(ip->ip_dst),ntohs(tcp->th_dport),ntohs(ip->ip_len));
			///printf("", );
			//printf("", );
			
            break;
        case IPPROTO_UDP:
            /*
              FILL HERE
              print source IP addr, source UDP port, destination IP addr, destination UDP port, IP length
              e.g., SA:00:25:bc:4c:8a:de  DA:00:1b:63:00:63:43  S_IP:10.0.2.4  S_PORT:80  D_IP:98.180.194.181  D_PORT:1377  IP_LEN:60 
            */
            udp =(struct sniff_udp*)((packet+layer2_size+size_ip));
			printf("S_IP:%s  S_PORT:%d  ", inet_ntoa(ip->ip_src),ntohs(udp->th_sport));			
			printf("D_IP:%s  D_PORT:%d  IP_LEN:%d\n", inet_ntoa(ip->ip_dst),ntohs(udp->th_dport),ntohs(ip->ip_len));
	    break;
        default:
            return;
    }

    return;
}

int main(int argc, char **argv)
{
    /* Read from .pcap FILE */
    if (argc != 2) {
	    printf("Usage: packet_info <file name>\n");
	    exit(EXIT_FAILURE);
    }

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_offline(argv[1], errbuf);

    if (handle == NULL) {
	    fprintf(stderr, "Could not open file %s\n", argv[1]);
	    exit(EXIT_FAILURE);
    }

    /* compile the filter expression */
    char filter_exp[] = "";		/* filter expression [3] */
    struct bpf_program fp;		/* compiled filter program (expression) */
    bpf_u_int32 netmask = 0; 	/* ip */
    int optimize=0;				/* Do not optimize the compiled expression in pcap_compile*/

    if (pcap_compile(handle, &fp, filter_exp, optimize, netmask) == -1) {
	    fprintf(stderr, "Could not parse filter %s: %s\n",
		    filter_exp, pcap_geterr(handle));
	    exit(EXIT_FAILURE);
    }

    /* apply the compiled filter */
    if (pcap_setfilter(handle, &fp) == -1) {
	    fprintf(stderr, "Could not install filter %s: %s\n",
		    filter_exp, pcap_geterr(handle));
	    exit(EXIT_FAILURE);
    }

    struct pcap_pkthdr first_pkthdr;
    first_pkthdr.ts.tv_sec = 0;
    first_pkthdr.ts.tv_usec = 0;
    u_char* user = (u_char*)&first_pkthdr;

    /* process the packet-capture file */
    int num_packets = -1;		/* The number of packets to capture; -1 indicates that pcap_loop should loop over all packets in the data file */
    u_char **user_input=&user; 	/* The "user_input" field allow data to be passed to the got_packet function*/
    pcap_loop(handle, num_packets, got_packet, (u_char*)user_input);

    /* cleanup */
    pcap_freecode(&fp);
    pcap_close(handle);

    return 0;
}

