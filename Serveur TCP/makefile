all: serveurMeteo g2serveurtcpmonoclient.o main.o

g2serveurtcpmonoclient.o: g2serveurtcpmonoclient.h g2serveurtcpmonoclient.cpp
	g++ -c g2serveurtcpmonoclient.cpp

main.o: main.cpp
	g++ -c main.cpp

serveurMeteo: g2serveurtcpmonoclient.o main.o
	g++ main.o g2serveurtcpmonoclient.o -o serveurMeteo

clean:
	rm -f g2serveurtcpmonoclient.o main.o serveurMeteo
