#include "../include/Player.h"

using namespace std;

int Player::nbPlayer=0;

Player::Player() {
	name="";
	score=0;
	valid=false;
	ia=false;
}

Player::Player(string nom) {
	name=nom;
	num=++nbPlayer;
	score=0;
	valid=true;
	ia=false;
}

void Player::Rename(string nom) {
	name=nom;
	valid=true;
}

void Player::Afficher() {
	if (!valid) return;
	cout<<"- name: "<<name<<" | num: "<<num<<" | Score: "<<score<<endl;
}

Player::~Player() {
	nbPlayer--;
}