// Inclusions des librairies nécessaires
#include <iostream>
#include <unistd.h>
#include <cerrno>
#include <sys/un.h>
#include <arpa/inet.h>

// Espace de nom utilisé
using namespace std;
// Point d'entrée du programme
int main()
{
	// Création de la socket en mode connecté (TCP)
	int sd = socket(AF_INET, SOCK_STREAM, 0);
	// Configuration des paramètres de connexion
	struct sockaddr_in adresse;
	adresse.sin_family = AF_INET;
	adresse.sin_port = htons(80);
	adresse.sin_addr.s_addr = inet_addr("212.27.63.110");
	// Connexion au serveur TCP
	connect(sd, (struct sockaddr *)&adresse, sizeof(struct sockaddr));

	// Envoi d'une requête au serveur
	string requete = "GET /web/index.php/feed/ HTTP/1.1\r\nHost: sandiris.free.fr\r\n\r\n";
	send(sd, requete.c_str(), requete.size(), 0);
	// Lecture de la réponse du serveur pour affichage
	char bufferReception[5024];
	memset(bufferReception, 0x00, 5024);
	int nbOctets = recv(sd, bufferReception, sizeof(bufferReception), 0);
	string reponse(bufferReception);
	cout << reponse << endl;
	// Fermeture de la socket
	close(sd);
	// Fin du programme
	return 0;
}
