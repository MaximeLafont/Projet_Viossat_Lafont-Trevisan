#pragma once

#include<iostream>
#include "personnage.hh"

class ETNormal: public ET{
private:
public:
	ETNormal(int x_init) : ET(x_init) {
		couleur.clear();
		couleur.push_back(165);
   		couleur.push_back(255);
   		couleur.push_back(65);
   		couleur.push_back(255);
	}

	~ETNormal(){};

};