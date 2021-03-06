// Librairies nécessaires
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
	 // Création de la socket serveur
	 int sd_serveur = socket(AF_INET, SOCK_STREAM, 0);
	 // Configuration de la socket, notamment le port d'écoute
	 struct sockaddr_in cfg_serveur;
	 cfg_serveur.sin_family = AF_INET;
	 cfg_serveur.sin_addr.s_addr = htonl(INADDR_ANY);
	 cfg_serveur.sin_port = htons(1664);
	 // Attachement de la socket au port défini
	 bind(sd_serveur, (struct sockaddr *)&cfg_serveur, sizeof(cfg_serveur));
	 // Création une file d'attente de connexion
	 listen(sd_serveur, 5);
	 while(1)
	 {
	 // Dès qu’un nouveau client se connecte à notre serveur,
	 // une nouvelle socket est créée pour gérer le client
	 int sd_client = accept(sd_serveur, NULL, NULL);
	 // Réception de la requête du client
	 char buffer[1024];
	 memset(buffer, 0x00, 1024);
	 int nbOctets = recv(sd_client, buffer, sizeof(buffer), 0);
	 string reponse(buffer);
	 cout << reponse << endl;
	 // Envoi de la réponse au client
	 string requete = "Hello world!";
	 send(sd_client, requete.c_str(), requete.size(), 0);
	 // Fermeture de la socket client
	 close(sd_client);
 }
 // Fermeture de la socket serveur
 close(sd_serveur);
 // Fin du programme
 return 0;
}
