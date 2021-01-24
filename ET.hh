#pragma once

#include<iostream>
#include "personnage.hh"

class ET: public personnage{
protected:
	int voler;
	int posy;
	
public:
	ET(int x_init) : personnage(x_init) {
   		voler = 2;
	}

	~ET(){};

	int get_voler(){
 		return voler;
 	}

 	void set_fvoler(int _voler){
 		this->voler = _voler;
 	}

 	int get_posy(){
 		return posy;
 	}

 	void set_posy(int y){
 		this->posy = y;
 	}

};