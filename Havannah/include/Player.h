#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

using namespace std;

class Player
{
	string name;				//nom du joueur
	int num;					//numérot du joueur
	int score;					//nombre de victoir du joueur (score)
	static int nbPlayer;		//le nombre de joueurs construits
	bool valid;					//Le joueur est valide
	bool ia;					//Le joueur est une IA ou non
	public:
		//!Constructeur par défault du joueur
		Player();
		//!Constructeur de joueur à partir d'une string
		/*!
			Initialise:\n
			-le nom du joueur\n
			-le numérot du joueur
			-incrémente le nombre de joueurs créés
			-rend le joueur valide
			-IA=false
			\param nom string correspondant au joueur
		*/
		Player(string nom);

		//!Fonction pour renomer le joueur
		void Rename(string);

		//!Affichage
		/*! Affiche les infos du joueur */
		void Afficher();

		//!Interface du nombre de joueurs
		/*! \return nbPlayer le nombre de joueurs créés */
		int nbJ(){return nbPlayer;};

		//!Interface du numérot du joueur
		/*! \return num le numérot du joueur */
		int numJ(){return num;};

		//! Destructeur de joueur
		/*! décrémente le nombre de joueurs créés */
		~Player();
};

#endif