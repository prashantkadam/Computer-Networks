all: proxy_server

proxy_server: http_proxy_server.cpp
	g++ -lpthread -g -o proxy http_proxy_server.cpp -lm
	./proxy
clean:
	rm -f *.o proxy
