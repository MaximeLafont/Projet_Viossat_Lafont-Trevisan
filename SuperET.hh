#pragma once

#include<iostream>
#include "ET.hh"

class SuperET: public ET{
private:
	
public:
	SuperET(int x_init) : ET(x_init) {

   		couleur.clear();
		couleur.push_back(255);
   		couleur.push_back(255);
   		couleur.push_back(0);
   		couleur.push_back(255);
		
		taille = 15;
	}

	float pouvoirET(float vitesse){
		return vitesse/2;
	}

	float fin_pouvoirET(float vitesse){
		return 1.5*vitesse;
	}

	~SuperET(){};

	



};