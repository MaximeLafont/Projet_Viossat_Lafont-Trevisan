#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include <random>

class meteorite{
private:
	std::vector<int> rect;
	std::string couleur;
	int posx;
	int posy;
public:
	meteorite(std::string _couleur,int XMAX,int YMAX): couleur(_couleur){
		if(couleur == "rouge"){
			rect.push_back(255);  
   			rect.push_back(0);
   			rect.push_back(0);
   			rect.push_back(255);
		}
		else if(couleur == "vert"){
			rect.push_back(0);  
   			rect.push_back(255);
   			rect.push_back(0);
   			rect.push_back(255);
		}
		else if(couleur == "bleu"){
			rect.push_back(0);  
   			rect.push_back(0);
   			rect.push_back(255);
   			rect.push_back(255);
		}
		std::default_random_engine _generator(std::chrono::system_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<int> distribution(0,XMAX);
		posx = (int) distribution(_generator);

		std::uniform_int_distribution<int> distribution2(0,YMAX);
		posy = (int) distribution2(_generator);
	}
	std::vector<int> get_rect(){
		return this->rect;
	}
	int get_posx(){
		return this->posx;
	}
	int get_posy(){
		return this->posy;
	}

	std::string get_couleur(){
		return this->couleur;
	}
	void set_posy(int y){
		this->posy = y;
	}
};