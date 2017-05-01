#include "../include/Plateau.h"

using namespace std;

Plateau::Plateau() {
	pair<int, int> ptmp;
	N=4;			//Taille
	T=new int *[(N*2)-1];
	for (int i=0; i<(N*2)-1; i++) {
		T[i]=new int [(N*2)-1];
		for (int j=0; j<(N*2)-1; j++) {
			if (j>=N+i || j<=i-N)
			{
				T[i][j]=-1;	//Les cases en dehors dé l'hexagone sort à -1
				continue;
			}
			else T[i][j]=0;				//les cases de l'hexagone sont à 0
			/*On détermine les coins*/
			if ( (i==0 && (j==0 || j==N-1)) || (i==N-1  && (j==0 || j==2*N-2)) || (i==N*2-2 && (j==N-1 || j==N*2-2)))
			{
				ptmp=make_pair(i, j);
				coin.insert(ptmp);
			}
			/*On détermine les cotés*/
				//haut gauche
			if ( (j==0 && (i>0 && i<N-1)) ) HG.insert(make_pair(i, j));
				//Haut milieu
			if ( (i==0 && (j>0 && j<N-1)) ) HM.insert(make_pair(i, j));
				//Haut droit
			if ( (j==i+N-1 && (i>0 && i<N-1)) ) HD.insert(make_pair(i, j));
				//Bas gauche
			if ( (j==i-(N-1) && (i>N-1 && i<2*N-2)) ) BG.insert(make_pair(i, j));
				//Bas milieu
			if ( (i==2*N-2 && (j>N-1 && j<2*N-2)) ) BM.insert(make_pair(i, j));
				//Bas droite
			if ( (j==2*N-2 && (i>N-1 && i<2*N-2)) ) BD.insert(make_pair(i, j));
		}
	}
	//AfficheCote();
}

Plateau::Plateau(int x) {
	pair<int, int> ptmp;
	N=x;			//Taille
	T=new int *[(N*2)-1];
	for (int i=0; i<(N*2)-1; i++) {
		T[i]=new int [(N*2)-1];
		for (int j=0; j<(N*2)-1; j++) {
			if (j>=N+i || j<=i-N)
			{
				T[i][j]=-1;	//Les cases en dehors dé l'hexagone sort à -1
				continue;
			}
			else T[i][j]=0;				//les cases de l'hexagone sont à 0
			/*On détermine les coins*/
			if ( (i==0 && (j==0 || j==N-1)) || (i==N-1  && (j==0 || j==2*N-2)) || (i==N*2-2 && (j==N-1 || j==N*2-2)))
			{
				ptmp=make_pair(i, j);
				coin.insert(ptmp);
			}
			/*On détermine les cotés*/
				//haut gauche
			if ( (j==0 && (i>0 && i<N-1)) ) HG.insert(make_pair(i, j));
				//Haut milieu
			if ( (i==0 && (j>0 && j<N-1)) ) HM.insert(make_pair(i, j));
				//Haut droit
			if ( (j==i+N-1 && (i>0 && i<N-1)) ) HD.insert(make_pair(i, j));
				//Bas gauche
			if ( (j==i-(N-1) && (i>N-1 && i<2*N-2)) ) BG.insert(make_pair(i, j));
				//Bas milieu
			if ( (i==2*N-2 && (j>N-1 && j<2*N-2)) ) BM.insert(make_pair(i, j));
				//Bas droite
			if ( (j==2*N-2 && (i>N-1 && i<2*N-2)) ) BD.insert(make_pair(i, j));
		}
	}
	//AfficheCote();
}

int Plateau::getTaille()
{
	return N;
}

bool Plateau::Possible(int x, int &y, int nbtour, bool gateau)
{
    int ajouty=0;
    if (x>=N)
    {
	ajouty=x-(N-1);
	y+=ajouty;
    }
    bool valid=true;
    if (x<0 || y<0 || x>2*N-2 || y>2*N-2) valid=false;	//vérif placer dans le plateau
    else if (T[x][y]<0)valid=false;			//Vérifie dans l'hexagone
    else if(nbtour!=1 && T[x][y]!=0) valid=false;	//vérif case occupée après 1er tour
    else if(!gateau && T[x][y]!=0) valid=false;		//Vérif gateau
    if (!valid) cout<<"Coordonnées invalides."<<endl;
    return valid;
}

bool Plateau::PossibleVoisin(int x, int y, int numj)
{
	bool valid=true;
	if (x<0 || y<0 || x>2*N-2 || y>2*N-2) valid=false;	//vérif placer dans le plateau
	else if (T[x][y]<0)valid=false;				//Vérifie dans l'hexagone
	else if (T[x][y]!=numj) valid=false;			//Vérifie si c'est bien l'un des voisins
	return valid;
}

void Plateau::Placer(Player *J, int x, int y)
{
    int nbj=J->nbJ();
    T[x][y]=J->numJ();		//On place à la coordonée choisie le numérot du joueur courant
}

bool Plateau::Gateau(int nbj, int &nbtour)		//Règle du gateau et compte le nombre de tours
{
    bool gateau=true;
    int numtour=0;
    for (int x=0; x<2*N-1; x++)
    {
        for (int y=0; y<2*N-1; y++)
        {
            if (T[x][y]>0)numtour++;
            if (nbj>2 || T[x][y]>1)gateau=false;	//on n'aplique pas la règle du gateau si le joueur 2 a joué ou que l'on as plus de 2 joueurs
        }
    }
    nbtour=numtour/nbj+1;		//Nb tour = (nbcases!=0/nbjours)+1
    return gateau;
}

void Plateau::Voisin(int x, int y, int xOrigine, int yOrigine, stack < pair<int, int> > &voisin, deque < pair<int, int> > &chemin)
{
	cerr<<"-----Voisins-----"<<endl;
	cerr<<"x: "<<x<<", y:"<<y<<endl;
	int nbj=T[x][y];
	deque < pair<int, int> >::iterator mit;
	pair <int, int> ptmp;
	for (int i=0; i<6; i++)
	{
		bool present=false;
		if(i==0) ptmp=make_pair(x-1, y-1);	//On parcours tous les différents voisins
		else if(i==1) ptmp=make_pair(x-1, y);
		else if(i==2) ptmp=make_pair(x, y-1);
		else if(i==3) ptmp=make_pair(x, y+1);
		else if(i==4) ptmp=make_pair(x+1, y);
		else if(i==5) ptmp=make_pair(x+1, y+1);
		cerr<<"pos x:"<<ptmp.first<<", y:"<<ptmp.second<<endl;
		if(PossibleVoisin(ptmp.first, ptmp.second, nbj)==false)continue;	//On regarde si le voisin existe
			//Si on retombe sur un voisin aillant les mêmes coordonées que le point d'origine de la vérification de la victoire
		if (ptmp.first==xOrigine && ptmp.second==yOrigine)	//Vérification boucle: si on retombe sur le voisin du départ
		{
			//chemin.insert(ptmp);
			bool boucle=verifBoucle(xOrigine, yOrigine, chemin);
		}
		
		for (mit=chemin.begin(); mit!=chemin.end(); mit++)		//On regarde si le voisin n'est pas déja présent
		{
			cerr<<"chemin x:"<<(*mit).first<<", y:"<<(*mit).second<<endl;
			if(ptmp.first==(*mit).first && ptmp.second==(*mit).second)present=true;
		}
		if(present==false)		//Si le voisin est possible
		{
			voisin.push(ptmp);
			chemin.push_back(ptmp);	//On le rajoute au chemin et aux voisins
			cerr<<"voisin x:"<<ptmp.first<<", y:"<<ptmp.second<<endl;
		}
		/*else
		{
				//On vérifie la boucle
				bool boucle=verifBoucle(ptmp, voisin);
			
		}*/
	}
	cerr<<"-----Voisins-Fin-----"<<endl;
}

void Plateau::verifWin(deque < pair<int, int> > chemin, bool &win)
{
	int angle=0;
	int nbCote=0;
	bool chg=false, ch=false, chd=false, cbg=false, cb=false, cbd=false; //Bool de tous les différents coins
	multimap<int, int>::iterator mitCoins;
	deque < pair<int, int> >::iterator mitChem;
	/*Vérificationd des angles*/
	for (mitChem=chemin.begin(); mitChem!=chemin.end(); mitChem++)
	{
		if(verifCoin(mitChem)) angle++;	//Chaques coordonées du chemins sont vérifiées, pour savoir si c'est un angle
	}
	cerr<<"nbAngle:"<<angle<<endl;
	if (angle>=2)
	{
		win=true;	//Si deux coins sont reliés alors c'est gagné!!!
		return;
	}
	
	/*Vérification de trois cotés différents*/
	for (mitChem=chemin.begin(); mitChem!=chemin.end(); mitChem++)
	{
		if(chg==false)
		{
			//Haut gauche
			chg=verifCote(mitChem, 1);
			if (chg==true) nbCote++;
		}
		if(ch==false)
		{
			//Haut milieu
			ch=verifCote(mitChem, 2);
			if (ch==true) nbCote++;
		}
		if(chd==false)
		{
			//Haut droit
			chd=verifCote(mitChem, 3);
			if (chd==true) nbCote++;
		}
		if(cbg==false)
		{
			//Bas gauche
			cbg=verifCote(mitChem, 4);
			if (cbg==true) nbCote++;
		}
		if(cb==false)
		{
			//Bas milieu
			cb=verifCote(mitChem, 5);
			if (cb==true) nbCote++;
		}
		if(cbd==false)
		{
			//Bas droit
			cbd=verifCote(mitChem, 6);
			if (cbd==true) nbCote++;
		}
	}
	cerr<<"nb Cotés:"<<nbCote<<endl;
	if (nbCote>=3)
	{
		win=true;	//Si trois cotés différents sont reliés C'est la Victoire!!!
		return;
	}
}

bool Plateau::verifCoin(deque < pair<int, int> >::iterator mitChem)
{
	//Vérifie si la coordonée est un coin de l'hexagone
	multimap<int, int>::iterator mitCoins;
	for (mitCoins=coin.begin(); mitCoins!=coin.end(); mitCoins++)
	{
		if((*mitChem).first==(*mitCoins).first && (*mitChem).second==(*mitCoins).second) return true;
	}
	return false;
}

bool Plateau::verifCote(deque < pair<int, int> >::iterator mitChem, int choix)
{
	//Choix détermine quelle coté vérifier
	multimap<int, int>::iterator mitCote;
	switch (choix)
	{
		case 1: //Haut gauche
			for (mitCote=HG.begin(); mitCote!=HG.end(); mitCote++)
			{
				if((*mitChem).first==(*mitCote).first && (*mitChem).second==(*mitCote).second) return true;
			}
			break;
		case 2: //Haut milieu
			for (mitCote=HM.begin(); mitCote!=HM.end(); mitCote++)
			{
				if((*mitChem).first==(*mitCote).first && (*mitChem).second==(*mitCote).second) return true;
			}
			break;
		case 3: //Haut droit
			for (mitCote=HD.begin(); mitCote!=HD.end(); mitCote++)
			{
				if((*mitChem).first==(*mitCote).first && (*mitChem).second==(*mitCote).second) return true;
			}
			break;
		case 4: //Bas gauche
			for (mitCote=BG.begin(); mitCote!=BG.end(); mitCote++)
			{
				if((*mitChem).first==(*mitCote).first && (*mitChem).second==(*mitCote).second) return true;
			}
			break;
		case 5: //Bas milieu
			for (mitCote=BM.begin(); mitCote!=BM.end(); mitCote++)
			{
				if((*mitChem).first==(*mitCote).first && (*mitChem).second==(*mitCote).second) return true;
			}
			break;
		case 6: //Bas droit
			for (mitCote=BD.begin(); mitCote!=BD.end(); mitCote++)
			{
				if((*mitChem).first==(*mitCote).first && (*mitChem).second==(*mitCote).second) return true;
			}
			break;
	}
}

bool Plateau::verifBoucle(int x, int y, deque < pair<int, int> > chemin)
{
	cerr<<"----Verif Boucle-------"<<endl;
	int nbj=T[x][y];
	bool Boucle=false;
	cerr<<"chemin:"<<endl;
	AfficherQueue(chemin);
	if (chemin.size()<6) return false;
	deque <pair <int, int> > boucle;
	recupBoucle(chemin, boucle);

	cerr<<"boucle:"<<endl;
	AfficherQueue(boucle);
	cerr<<"----fin Verif Boucle-------"<<endl;
	return Boucle;
	//int compt=0;
	//on vérifie x fixe; y->+
	//x fixe; y->-
	//x->+; y fixe
	//x->-; y fixe
	//x->+; y->+
	//x->-; y->-
}

void Plateau::recupBoucle(deque < pair<int, int> > chemin, deque < pair<int, int> > & boucle)
{
	cerr<<"----recup Boucle----"<<endl;
	deque < pair<int, int> > visited;
	deque < pair<int, int> >::iterator itChem, itBoucl;
	pair <int, int> pChem=chemin.front();
	int x=pChem.first;
	int xOrigine=x;
	int y=pChem.second;
	int yOrigine=y;
	itChem=chemin.begin();
	boucle.push_back(chemin.front());
	pair <int, int> pBoucl=boucle.back();
	visited.push_back(pBoucl);

	
	
	voisinBoucle(x, y, xOrigine, yOrigine, chemin, boucle, visited);
	cerr<<"x:"<<pChem.first<<", y:"<<pChem.second<<endl;

	while (pBoucl.first!=xOrigine && pBoucl.second!=yOrigine && boucle.size()<6)
	{
		cerr<<"la"<<endl;
		voisinBoucle(pBoucl.first, pBoucl.second, xOrigine, yOrigine, chemin, boucle, visited);
		pBoucl=boucle.back();
	}
	boucle.pop_back();
	cerr<<"----recup Boucle----"<<endl;
}

void Plateau::voisinBoucle(int x, int y, int xOrigine, int yOrigine, deque < pair<int, int> > chemin, deque < pair<int, int> > & boucle, deque < pair<int, int> > & visited)
{
	cerr<<"-----Voisins Boucle-----"<<endl;
	bool found=false;
	deque <pair <int, int> >::iterator itChem, itBoucl, itVis;
	int numJ=T[x][y];
	pair <int, int> ptmp;
	int i=0;
	while (i<6)
	{
		cerr<<"li"<<endl;
		bool bVisited=false;
		if(i==0) ptmp=make_pair(x-1, y-1);	//On parcours tous les différents voisins
		else if(i==1) ptmp=make_pair(x-1, y);
		else if(i==2) ptmp=make_pair(x, y-1);
		else if(i==3) ptmp=make_pair(x, y+1);
		else if(i==4) ptmp=make_pair(x+1, y);
		else if(i==5) ptmp=make_pair(x+1, y+1);
		
		if (PossibleVoisin(ptmp.first, ptmp.second, numJ)==false)
		{
			i++;
			continue;
		}

		if (ptmp.first==xOrigine && ptmp.second==yOrigine && boucle.size()>=6)
		{
			boucle.push_back(ptmp);
			return;
		}

		for (itVis=visited.begin(); itVis!=visited.end(); itVis++)
		{
			if(ptmp.first==(*itVis).first && ptmp.second==(*itVis).second)
			{
				bVisited=true;
			}
		}

		if (!bVisited)
		{
			visited.push_back(ptmp);
			boucle.push_back(ptmp);
		}
		i++;
		if (i>=6)
		{
			boucle.pop_back();
		}
	}
	cerr<<"-----Fin Voisins Boucle-----"<<endl;
}

/*void Plateau::Afficher() {
	//Afficge de manière bourine
	for (int i=0; i<((N*2)-1); i++) {
		cout<<"|";
		for (int j=0; j<((N*2)-1); j++) {
			cout<<T[i][j]<<"|";
		}
		cout<<endl;
	}
}*/

void Plateau::Afficher()
{
	int espace=0;
	for (int i=0; i<(N*2)-1; i++)
	{
		if (i<=(N-1)) espace=((N*2)-1)-(N+i);
		else
		{
			int compt=0;
			for (int j=0; j<((N*2)-1); j++)
			{
				if (T[i][j]!=-1)compt++;
			}
			//cout<<"compt="<<compt<<endl;
			espace=((N*2)-1)-compt;
		}
		//cout<<"espace="<<espace<<endl;
		for (int j=0; j<espace; j++) cout<<" ";
		for (int j=0; j<((N*2)-1); j++)
		{
			if (T[i][j]==0) cout<<". ";
			else if (T[i][j]!=-1) cout<<T[i][j]<<" ";
		}
		cout<<endl;
	}
}

void Plateau::Affichecoins()
{
	multimap<int, int>::iterator mit;
	for (mit=coin.begin(); mit!=coin.end(); mit++)
	{
		cout<<"x:"<<(*mit).first<<" ,y:"<<(*mit).second<<endl;
	}
}

void Plateau::AfficheCote()
{
	multimap<int, int>::iterator mit;
	cout<<"Liste de cotés: "<<endl;
	cout<<"Haut gauche: "<<endl;
	for (mit=HG.begin(); mit!=HG.end(); mit++)
	{
		cout<<"x:"<<(*mit).first<<" ,y:"<<(*mit).second<<endl;
	}
	cout<<"Haut milieu: "<<endl;
	for (mit=HM.begin(); mit!=HM.end(); mit++)
	{
		cout<<"x:"<<(*mit).first<<" ,y:"<<(*mit).second<<endl;
	}
	cout<<"Haut droit: "<<endl;
	for (mit=HD.begin(); mit!=HD.end(); mit++)
	{
		cout<<"x:"<<(*mit).first<<" ,y:"<<(*mit).second<<endl;
	}
	cout<<"Bas gauche: "<<endl;
	for (mit=BG.begin(); mit!=BG.end(); mit++)
	{
		cout<<"x:"<<(*mit).first<<" ,y:"<<(*mit).second<<endl;
	}
	cout<<"Bas milieu: "<<endl;
	for (mit=BM.begin(); mit!=BM.end(); mit++)
	{
		cout<<"x:"<<(*mit).first<<" ,y:"<<(*mit).second<<endl;
	}
	cout<<"Bas droite: "<<endl;
	for (mit=BD.begin(); mit!=BD.end(); mit++)
	{
		cout<<"x:"<<(*mit).first<<" ,y:"<<(*mit).second<<endl;
	}
}

void AfficherMap(multimap <int,int> Map)
{
	multimap<int, int>::iterator mit;
	for (mit=Map.begin(); mit!=Map.end(); mit++)
	{
		cout<<"x:"<<(*mit).first<<" ,y:"<<(*mit).second<<endl;
	}
}

void AfficherQueue(deque < pair<int, int> > Queue)
{
	deque< pair<int, int> >::iterator qit;
	for (qit=Queue.begin(); qit!=Queue.end(); qit++)
	{
		cout<<"x:"<<(*qit).first<<" ,y:"<<(*qit).second<<endl;
	}
}

