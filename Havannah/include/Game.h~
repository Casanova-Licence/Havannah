#ifndef GAME_H
#define GAME_H

#include "../include/Plateau.h"
#include "../include/Player.h"

#include <iostream>
#include <vector>
#include <deque>
#include <stack>

using namespace std;

class Game
{
	Plateau P; 		//Plateau de jeux
	deque<Player *> tours; 	//Queue de joueurs, représentant la liste des joueurs et leurs ordre de passage	

	public:
		//!Constructeur d'une partie
		/*!
			lance le jeux
			\sa StartMenu()
		*/
		Game();

		//!Lance le jeux
		/*!
			sélectionne le mode de jeux\n
			\sa JCJ()
		*/
		void StartMenu();
		
		//!Initialise les éléments nécessaire pour une partie
		/*!
			-Initialise la queue de joueurs\n
			-Initialise le plateau
			\sa GameJCJ()
		*/
		void JCJ();

		//!Gère une partie joueurs vs joueurs
		/*!
			Gère tours par tours les actions des 2 joueurs:\n
				-utilise la règle du gateau (au 1er tour),\n
				-le joueur du tour choisie ou placer so pion: coordonées (x,y),\n
				-Vérifie si le coup est gagnant
			\sa win(int x, int y)
			\sa 
		*/
		void GameJCJ();

		//!Vérifie si le coup est gangant
		/*!
			\param x: coordoné x du dernier pion posé
			\param y: coordonée y du dernier pion posé
			\return true: le coup est gagnant
			\return false: sinon
		*/
		bool win(int x, int y);

		void JCIA();
};

	//!Debug
	/*!
		Affiche les infos contenus dans une multimap
		\param Map multimap <int,int> représentant une map de coordonées <x,y>
	*/
	void AfficherMap(multimap <int,int> Map);

//void AfficherStack(stack < pair<int, int> > stack);

#endif
