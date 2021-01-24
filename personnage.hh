#pragma once

#include <iostream>

typedef enum  Type {HN, SH, EN, SE}  Type;

void print(Type type){
	switch (type){
		case (HN): std :: cout << "HN" << std::endl;
			break;
		case (SH): std :: cout << "SH" << std::endl;
			break;
		case (EN): std :: cout << "EN" << std::endl;
			break;
		case (SE): std :: cout << "SE" << std::endl;
			break;
	}
}

class personnage{
protected:
	int vie;
	int posx;
	std::vector<int> couleur;
	int taille;
	int deplacement;

 public:
 	personnage(int x_init)
 	{
 		vie=3;
 		posx = x_init;
 		taille=20;
 		deplacement = 3;
		couleur.push_back(255);
   		couleur.push_back(0);
   		couleur.push_back(255);
   		couleur.push_back(255);	
   	}

   	~personnage(){};

 	int get_vie()const{
 		return this->vie;
 	}

 	int get_posx()const{
 		return posx;
 	}

 	int get_taille()const{
 		return taille;
 	}

 	int get_deplacement()const{
 		return deplacement;
 	}

 	std::vector<int> get_couleur(){
		return this->couleur;
	}

 	void set_vie(int _vie){
 		this->vie = _vie;
 	}

 	void set_posx(int x){
 		this->posx = x;
 	}

 	void set_taille(int _taille){
 		this->taille = _taille;
 	}

 	void set_deplacement(int _deplacement){
 		this->deplacement = _deplacement;
 	}

 	void set_couleur(int col1, int col2, int col3, int col4){
   		this->couleur[0]=col1;
		this->couleur[1]=col2;
		this->couleur[2]=col3;
		this->couleur[3]=col4;
 	}

 	virtual void pouvoir(){};

 	virtual void fin_pouvoir(){};

};
