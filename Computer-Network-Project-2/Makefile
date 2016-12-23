all: clean dissector 

dissector:
	gcc -g -Wall -o dissector dissector.c -lpcap
run1:
	./dissector sample1.pcap
run2:
	./dissector sample2.pcap
clean:
	rm -f dissector *~
