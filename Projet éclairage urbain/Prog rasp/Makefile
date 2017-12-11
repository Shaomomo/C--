CC=g++ 
CFLAGS=-c -Wall

all: Serveur main.o serveurLORA.o serveurTCP.o serveurHTTP.o creationHTML.o SNPortSerie.o MessageCAN.o VSCOM.o SNIRconversions.o

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -std=c++11

serveurLORA.o: serveurLORA.cpp serveurLORA.h
	$(CC) $(CFLAGS) serveurLORA.cpp

serveurTCP.o: serveurTCP.cpp serveurTCP.h
	$(CC) $(CFLAGS) serveurTCP.cpp

serveurHTTP.o: serveurHTTP.cpp serveurHTTP.h
	$(CC) $(CFLAGS) serveurHTTP.cpp

creationHTML.o: creationHTML.cpp creationHTML.h
	$(CC) $(CFLAGS) creationHTML.cpp

SNIRconversions.o:SNIRconversions.cpp SNIRconversions.h
	g++ -c SNIRconversions.cpp

SNPortSerie.o: SNPortSerie.h SNPortSerie.cpp
	g++ -c SNPortSerie.cpp

VSCOM.o: VSCOM.cpp VSCOM.h
	g++ -c VSCOM.cpp

MessageCAN.o: MessageCAN.cpp MessageCAN.h
	g++ -c MessageCAN.cpp

Serveur: main.o serveurLORA.o serveurTCP.o serveurHTTP.o creationHTML.o MessageCAN.o VSCOM.o SNIRconversions.o SNPortSerie.o
	$(CC) main.o serveurLORA.o serveurTCP.o serveurHTTP.o creationHTML.o MessageCAN.o VSCOM.o SNIRconversions.o SNPortSerie.o -lpthread -o Serveur 

clean :
	rm -f *.o Serveur
