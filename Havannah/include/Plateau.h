#ifndef PLATEAU_H
#define PLATEAU_H

#include <iostream>
#include <map>
#include <stack>

#include "../include/Player.h"

using namespace std;

class Plateau
{
	int N;			//Taille du plateau
	int **T;		//Le plateau d'entier
	multimap<int, int> coin;	//Liste tous les coins (Angles)
	/*Liste des cotés*/
	multimap<int, int> HG;	//Haut gauche
	multimap<int, int> HM;	//Haut milieu
	multimap<int, int> HD;	//Haut droite
	multimap<int, int> BG;	//Bas gauche
	multimap<int, int> BM;	//Bas milieu
	multimap<int, int> BD;	//Bas droite
	public:
		
		//!Constructeur par défault de Plateau
		/*! Taille initiale N=4*/
		Plateau();

		//!Constructeur à partir d'un int
		/*!
			taille du plateau = x\n
			Initialise les cotés, et les coins de l'hexagone\n
			\n
			Ex: x=4:\n
			Tableau géré par le programme\n
			[0 0 0 0 -1 -1 -1]\n
			[0 0 0 0 0 -1 -1]\n
			[0 0 0 0 0 0 -1]\n
			[0 0 0 0 0 0 0]\n
			[-1 0 0 0 0 0 0]\n
			[-1 -1 0 0 0 0 0]\n
			[-1 -1 -1 0 0 0 0]\n
			-----------------------------\n
			Tableau perçu par le joueur\n
			[0 0 0 0 -1 -1 -1]\n
			[0 0 0 0 0 -1 -1]\n
			[0 0 0 0 0 0 -1]\n
			[0 0 0 0 0 0 0 0]\n
			[0 0 0 0 0 0 -1]\n
			[0 0 0 0 0 -1 -1]\n
			[0 0 0 0 -1 -1 -1]\n
			0: Plaçable ; -1: Implaçable
			
			\param x représentant la taille du plateau à construir
		*/
		Plateau(int x);

		
		
		//!Fonction pour qu'un joueur puisse placé son pion
		/*!
			\param J Player concerné
			\param x coordonée x
			\param y coordonée y
		*/
		void Placer(Player *J, int x, int y);

		//!Fonction pour vérifier si on applique la règle du gateau
		/*!
			Détermine si on fait la règle du gateau, et calcul le numérot du tour
			\param nbj entier représentant le nombre de joueurs
			\param nbtour entier représentant le numérot du tour
			\return true: on applique la règle du gateau
			\return false: on ne l'applique pas
		*/
		bool Gateau(int nbj, int &nbtour);

		/*Retoure +/- utiles*/
		//!Interface de la valeur située à une sertaine position
		/*!
			\param x coordonée x
			\param y coordonée y
			\return un entier représentant la valeur du plateau aux coordonées (x,y)
		*/
		int val(int x, int y){return T[x][y];};

		//!Interface de la taille du plateau
		/*! \return un entier représentant la taille du plateau */
		int getTaille();
		
		/*Fonctions vérif victoire*/
		//!Vérifie si le joueur peut poser
		/*!
			En fonction des coordonées (x,y), du tour et de la règle du gateau, le joueur peut placer le pion à différetns endroits
			\param x coordonée x
			\param y coordonée (modifiée pour pouvoir considérer le tableau de manière différente pour le poins de vue du joueur)
			\param nbtour le numérot du tour
			\param gateau booléein indiquant si on applique la règle du gateau ou non lors du placement

			\return true: le coup peut-être joué
			\return false: sinon
		*/
		bool Possible(int x, int &y, int nbtour, bool gateau);

		//!Fonction pour vérifier si un voisin est valide
		/*!
			Vérifie que le voisin est bien valide:\n
			-Il est situé dans l'hexagone\n
			-Il est bel et bien un voisin (num case == numj)

			\param x coordonée x du vosin à vérifier la validitée
			\param y coordonée y du vosin à vérifier la validitée
			\param numj numérot du joueur
			\sa Voisin()
		*/
		bool PossibleVoisin(int x, int y, int numj);

		//!Fonction récupérant les voisins de la case (x,y)
		/*!
			remplie une pile de coordonées des voisins de la case (x, y),\n
			Veille à ce que le voisin soit valide et qu'il ne soit pas déjà présent dans le chemin de coordonées
			\param x coordonée x
			\param y coordonée y
			\param voisin Pile de coordonées dont il faudra chercher les voisins 
			\param chemin liste les coordonées déjà parcourues

			\return true: la case est bien un voisin
			\return false: sinon

			\sa PossibleVoisin()
		*/
		void Voisin(int x, int y, stack < pair<int, int> > &voisin, multimap <int, int> &chemin);

		//!Fonction pour vérifier la victoire par un pont et uen fourche
		/*!
			\param chemin liste de coordonées voisines l'unes de l'autre
			\param win bool informant si le joueur à gagner ou non

			\sa verifCoin()
			\sa verifCote()
		*/
		void verifWin(multimap <int, int> chemin, bool &win);

		//!Fonction pour vérifier si la coordonée est un coin
		/*!
			Vérifie que la coordonée (x, y) pointée par l'itérateur fait partie de l'un des coins de l'hexagone
			\param mitChem itérateur contenant l'adresse d'une pair de coordonées (x, y) d'une des cases du chemin

			\return true: la coordonée est l'un des coins
			\return false: sinon
		*/
		bool verifCoin(multimap <int, int>::iterator mitChem);

		//!Fonction pour vérifier si la coordonée fait partie de l'un des coins
		/*!
			Vérifie si la cordonée fait parte de l'un des coins (celon le choix)
			\param mitChem itérateur contenant l'adresse d'une pair de coordonées (x, y) d'une des cases du chemin
			\param choix int représentant le choix du coté de l'hexagone à vérifier:\n
				1: haut gauche\n
				2: haut milier\n
				3: haut droite\n
				4: bas gauche\n
				5: bas milieu\n
				6: bas droite

			\return true: la coordonée fait partie du coin sélectionné
			\return false: sinon
		*/
		bool verifCote(multimap <int, int>::iterator mitChem, int choix);

		//bool verifBoucle(pair <int, int> last);

		/*Affichages*/
		//!Fonction debug
		/*! Affiche les coordonées des coins de l'hexagone */
		void Affichecoins();

		//!Fonction debug
		/*! Affiche les cotés coordonées des poins situés sur les cotés de l'hexagone */
		void AfficheCote();

		//!Affichage
		/*! Affiche l'hexagone*/
		void Afficher();
};

#endif
