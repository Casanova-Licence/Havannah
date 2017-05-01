#include "../include/Game.h"

using namespace std;

Game::Game()
{
	StartMenu();
}

void Game::StartMenu() {
	cout<<endl;
	cout<<" /$$   /$$  /$$$$$$  /$$    /$$  /$$$$$$  /$$   /$$ /$$   /$$  /$$$$$$  /$$   /$$"<<endl;
	cout<<"| $$  | $$ /$$__  $$| $$   | $$ /$$__  $$| $$$ | $$| $$$ | $$ /$$__  $$| $$  | $$"<<endl;
	cout<<"| $$  | $$| $$  \\ $$| $$   | $$| $$  \\ $$| $$$$| $$| $$$$| $$| $$  \\ $$| $$  | $$"<<endl;
	cout<<"| $$$$$$$$| $$$$$$$$|  $$ / $$/| $$$$$$$$| $$ $$ $$| $$ $$ $$| $$$$$$$$| $$$$$$$$"<<endl;
	cout<<"| $$__  $$| $$__  $$ \\  $$ $$/ | $$__  $$| $$  $$$$| $$  $$$$| $$__  $$| $$__  $$"<<endl;
	cout<<"| $$  | $$| $$  | $$  \\  $$$/  | $$  | $$| $$\\  $$$| $$\\  $$$| $$  | $$| $$  | $$"<<endl;
	cout<<"| $$  | $$| $$  | $$   \\  $/   | $$  | $$| $$ \\  $$| $$ \\  $$| $$  | $$| $$  | $$"<<endl;
	cout<<"|__/  |__/|__/  |__/    \\_/    |__/  |__/|__/  \\__/|__/  \\__/|__/  |__/|__/  |__/"<<endl<<endl;

	cout<<"                             Player versus Player"<<endl;
	cout<<"                                 --Press-1--"<<endl;
	cout<<"                             Player versus IA"<<endl;
	cout<<"                                 --Press-2--"<<endl;
	int c;
	cin>>c;
	while (c!=1 && c!=2) {
		cin>>c;
	}
	system("clear");
	switch (c) {
		case 1: {
			JCJ();
			break;
		}
		case 2: {
			JCIA();
			break;
		}
	}
}

void Game::JCJ() {
	cout<<"                           ___                  ___ "<<endl;
	cout<<"                          / _ \\   /\\   /\\      / _ \\"<<endl;
	cout<<"                         / /_)/___\\ \\ / /____ / /_)/"<<endl;
	cout<<"                        / ___/_____\\ V /_____/ ___/ "<<endl;
	cout<<"                        \\/          \\_/      \\/     "<<endl<<endl;

	cout<<"                                Deux Joueurs"<<endl;
	cout<<"                                --Press-1--"<<endl;
	cout<<"                               Trois Joueurs"<<endl;
	cout<<"                                --Press-2--"<<endl;
	Player *J;
	int c;
	int n;
	cin>>c;
	while (c!=1 && c!=2) {
		cin>>c;
	}
	switch (c) {
		case 1: {
			string nom;
			cout<<"Saisissez le nom du joueur 1"<<endl;
			cin>>nom;
			J=new Player(nom);
			J->Afficher();
			tours.push_back(J);
			cout<<"Saisissez le nom du joueur 2"<<endl;
			cin>>nom;
			J=new Player(nom);
			J->Afficher();
			tours.push_back(J);
			break;
		}
		case 2: {
			string nom;
			cout<<"Saisissez le nom du joueur 1"<<endl;
			cin>>nom;
			J=new Player(nom);
			J->Afficher();
			tours.push_back(J);
			cout<<"Saisissez le nom du joueur 2"<<endl;
			cin>>nom;
			J=new Player(nom);
			J->Afficher();
			tours.push_back(J);
			cout<<"Saisissez le nom du joueur 3"<<endl;
			cin>>nom;
			J->Afficher();
			J=new Player(nom);
			tours.push_back(J);
			break;
		}
	}
	cout<<"choisissez la taille du plateau entre 4 et 10 compris:"<<endl;
	cin>>n;
	while (n<4 && n>10)
	{
		cin>>n;
	}
	P=Plateau(n);
	GameJCJ();
}


  /**************/
 /**Partie JCJ**/
/**************/
void Game::GameJCJ()
{
    int n=P.getTaille();
    int nbtour=1;
    //int nbj=J1->nbJ();
    int nbj=tours.front()->nbJ();
    Player *current;
    bool Fin=false;
    while (!Fin)
    {
        bool gateau=P.Gateau(nbj, nbtour);	//On détermine le topur et si on doit appliquer la règle du gateau
        cout<<"tour: "<<nbtour<<endl;
        int x=2*n-2,y=0;			//Initialisation des coordonées où insérer
        P.Afficher();
        current=tours.front();			//On récupère le joueur du tour
        current->Afficher();
        cout<<"choisissez les coordonnées"<<endl;
        cout<<"x: ";
        cin>>x;
        cout<<"y: ";
        cin>>y;
        while (P.Possible(x, y, nbtour, gateau)==false)	//On vérifie que les coordonées soient valide
        {
            cout<<"choisissez les coordonnées:"<<endl;
            cout<<"x: ";
            cin>>x;
            cout<<"y: ";
            cin>>y;
        }
        P.Placer(current, x, y);	//Si valide placer
	Fin=win(x, y);		//On vérifie si le coup est gagnant
        tours.push_back(current);	//On replace le joueur dans la queue
        tours.pop_front();
    }
    cout<<"Bravo!"<<endl;
}

bool Game::win(int x, int y)
{
	cerr<<"____________Win verif__________"<<endl;
	int xtmp, ytmp;
		//identifiant du joueur
	int idp=P.val(x, y);
	bool win=false;
	stack < pair<int, int> > voisin; //Pile contenant les cases à vérifier
	pair<int, int> ptmp;		 //Paire de position
	deque< pair<int, int> > chemin;	 //Queue pour éviter de remettre 2x la meme position
	ptmp=make_pair(x, y);
	voisin.push(ptmp);
	chemin.push_back(ptmp);
	//P.Affichercoins();
	while (!voisin.empty()) //Récupérer les voisins
	{
		ptmp=voisin.top();
		cerr<<"x="<<ptmp.first<<" y="<<ptmp.second<<endl;
		voisin.pop();
		P.Voisin(ptmp.first, ptmp.second, x, y, voisin, chemin);
		//AfficherQueue(chemin);
	}
	AfficherQueue(chemin);
	//Vérifie si le chemin permet de gagner
	P.verifWin(chemin, win);
	cerr<<"____________Fin Win verif__________"<<endl;
	return win;
}


  /**************/
 /*Partie  JCIA*/
/**************/
void Game::JCIA()
{
	cout<<"                         ___                 _____  _   "<<endl;
	cout<<"                        / _ \\   /\\   /\\      \\_   \\/_\\  "<<endl;
	cout<<"                       / /_)/___\\ \\ / /____   / /\\//_\\\\ "<<endl;
	cout<<"                      / ___/_____\\ V /_____/\\/ /_/  _  \\"<<endl;
	cout<<"                      \\/          \\_/      \\____/\\_/ \\_/"<<endl;
}







  /*********/
 /* Debug */
/*********/




/*void AfficherMap(multimap <int,int> Map)
{
	multimap<int, int>::iterator mit;
	for (mit=Map.begin(); mit!=Map.end(); mit++)
	{
		cout<<"x:"<<(*mit).first<<" ,y:"<<(*mit).second<<endl;
	}
}*/

/*void AfficherStack(stack < pair<int, int> > stack)
{
	stack< pair<int, int> >::iterator sit;
	for (sit=stack.begin(); sit!=stack.end(); sit++)
	{
		cout<<"x:"<<(*sit).first<<" ,y:"<<(*sit).second<<endl;
	}
}*/
