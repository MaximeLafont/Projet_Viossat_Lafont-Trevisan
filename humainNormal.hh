#pragma once

#include<iostream>
#include "humain.hh"

class humainNormal: public humain{
private:
	
public:
	humainNormal(int x_init) : humain(x_init) {
		couleur.clear();
		couleur.push_back(0);
   		couleur.push_back(255);
   		couleur.push_back(255);
   		couleur.push_back(255);
   		taille = 20;
	}

	~humainNormal(){};



};