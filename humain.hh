#pragma once

#include<iostream>
#include "personnage.hh"

class humain: public personnage{
protected:
	int bouclier;
	
public:
	humain(int x_init) : personnage(x_init) {
   		bouclier = 0;
	}

	~humain(){};

	int get_bouclier(){
 		return bouclier;
 	}

 	


};