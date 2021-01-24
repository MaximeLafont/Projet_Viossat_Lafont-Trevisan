#pragma once

#include<iostream>
#include "humain.hh"

class SuperHumain: public humain{
private:
	
public:
	SuperHumain(int x_init) : humain(x_init) {
		couleur.clear();
		couleur.push_back(255);
   		couleur.push_back(165);
   		couleur.push_back(0);
   		couleur.push_back(255);
   		taille = 15;
	}

	~SuperHumain(){};

	void pouvoir(){
		this -> bouclier = 1;
	}

	void fin_pouvoir(){
		this -> bouclier = 0;
	}


};