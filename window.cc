#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h> 
#include <iostream>
#include <list>
#include "meteorite.hh"
#include "personnage.hh"
#include "humain.hh"
#include "humainNormal.hh"
#include "SuperHumain.hh"

#include "ET.hh"
#include "ETNormal.hh"
#include "SuperET.hh"

  
int main(int argc, char ** argv)
{
    // variables

    // dimensions de la fenêtre
    int XMAX = 960;
    int YMAX = 720;

    // temps et délais des différentes actions
    Uint32 temps = 0;
    Uint32 temps_prec = 0;
    Uint32 temps_pouvoir;
    Uint32 palier_temps = 0;

    int delai = 500;
    int duree_pouvoir = 15000;
    int delai_activation_pouvoir = 20000;
    int acceleration_meteorite = 10000;
    int nb_meteorites = 2;

    // taille initiale des objets
    int taille_met = 10;
    int taille_pers = 20;

    int x,y;

    // initialisation du jeu
    float vitesse = (temps/10000)^(4/3)+1;
    int jeu = 0;
    int vie = 3;
    int pouvoir = -1;
    int autorisation_pouvoir = 1;

    int mx,my;
    // variable du type de personnage 
    Type type;

    // génarateur de nombres aléatoires afin de déterminer la couleur des météorites selon les proportions données
    std::default_random_engine _generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(0,100);
    int couleur, prop_bleu = 10, prop_vert = 5;
     
    bool quit = false;
    SDL_Event event;
     
    // initialisation SDL
     
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_Window * window = SDL_CreateWindow("L'Apocalypse",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, XMAX, YMAX, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, 0, -1);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Texture * texture_looseGame;
    SDL_Surface *looseGame;
    looseGame = IMG_Load("perdu_512x324.png");
    texture_looseGame = SDL_CreateTextureFromSurface(renderer, looseGame);

    TTF_Font* Sans = TTF_OpenFont("sans.ttf", 25);
    TTF_Font* Sans2 = TTF_OpenFont("sans.ttf", 15);


    
    std::vector<meteorite> meteorites;

    // Initialisation des personnages

    humainNormal Pers1(XMAX/2);
    SuperHumain Pers2(XMAX/2);
    ETNormal Pers3(XMAX/2);
    SuperET Pers4(XMAX/2);    

    taille_pers = Pers1.get_taille();
    int deplacement = Pers1.get_deplacement();
    int voler = Pers3.get_voler();

    SDL_Rect pers = { XMAX/2, YMAX-taille_pers, taille_pers, taille_pers };

    SDL_Rect Message_rect_humain;
    SDL_Rect Message_rect_ET; 

   
   
    while (!quit)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        if (jeu == 0){ // Affichage du menu choix du mode de jeu
            

            SDL_Color col = {255, 0, 255};
            
            SDL_Surface* surfaceMessage_humain = TTF_RenderText_Solid(Sans, "Mode Humain", col);
            SDL_Texture* Message_humain = SDL_CreateTextureFromSurface(renderer, surfaceMessage_humain);

            SDL_Surface* surfaceMessage_ET = TTF_RenderText_Solid(Sans, "Mode ET", col);
            SDL_Texture* Message_ET = SDL_CreateTextureFromSurface(renderer, surfaceMessage_ET);

            
            Message_rect_humain.x = XMAX/2-surfaceMessage_humain->w/2;  
            Message_rect_humain.y = YMAX/3; 
            Message_rect_humain.w = surfaceMessage_humain->w; 
            Message_rect_humain.h = surfaceMessage_humain->h; 

            Message_rect_ET.x = XMAX/2-surfaceMessage_ET->w/2;  
            Message_rect_ET.y = YMAX/2; 
            Message_rect_ET.w = surfaceMessage_ET->w; 
            Message_rect_ET.h = surfaceMessage_ET->h; 

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

            SDL_RenderFillRect(renderer, &Message_rect_humain);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &Message_rect_ET);

            SDL_RenderCopy(renderer, Message_humain, NULL, &Message_rect_humain);
            SDL_DestroyTexture(Message_humain);
            SDL_FreeSurface(surfaceMessage_humain);

            SDL_RenderCopy(renderer, Message_ET, NULL, &Message_rect_ET);
            SDL_DestroyTexture(Message_ET);
            SDL_FreeSurface(surfaceMessage_ET);
        
        }
        else{
            

            // Affichage du nombre de vies restantes 

            SDL_Color col = {0, 0, 0};

            char mess[10] = "";
            switch(type)
                        {
                            case (HN): sprintf(mess, "Vie : %d", Pers1.get_vie());
                                break;
                            case (SH): sprintf(mess, "Vie : %d", Pers2.get_vie());
                                break;
                            case (EN): sprintf(mess, "Vie : %d", Pers3.get_vie());
                                break;
                            case (SE): sprintf(mess, "Vie : %d", Pers4.get_vie());
                                break;            
                        }
            
            SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, mess, col);
            SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 

            SDL_Rect Message_rect; 
            Message_rect.x = XMAX/2-surfaceMessage->w/2;
            Message_rect.y = 50; 
            Message_rect.w = surfaceMessage->w; 
            Message_rect.h = surfaceMessage->h; 

            SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
            SDL_DestroyTexture(Message);
            SDL_FreeSurface(surfaceMessage);

            if (pouvoir == 0 && vie > 0){
                char mess[50] = "Appuyez sur A pour activer votre pouvoir";
                SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans2, mess, col);
                SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

                SDL_Rect Message_rect; 
                Message_rect.x = XMAX/2-surfaceMessage->w/2;
                Message_rect.y = 100; 
                Message_rect.w = surfaceMessage->w; 
                Message_rect.h = surfaceMessage->h; 

                SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
                SDL_DestroyTexture(Message);
                SDL_FreeSurface(surfaceMessage);
            }

            if (temps - palier_temps > acceleration_meteorite && nb_meteorites < 35){ // Augmentation du nombre de météorites créées
                palier_temps = temps;
                nb_meteorites += 1;
            }

            if ((temps >= (temps_prec + delai )) || (temps == 0)) // Création des météorites
            {
                temps_prec = temps;
                for(int i = 0; i<nb_meteorites;i++){
                    couleur = (int) distribution(_generator);
                    if (couleur < prop_bleu)
                    {
                        meteorite m("bleu",XMAX,0);
                        meteorites.push_back(m);
                    }
                    else if(couleur < prop_bleu + prop_vert)
                    {
                        meteorite m("vert",XMAX,0);
                        meteorites.push_back(m);
                    }
                    else
                    {
                        meteorite m("rouge",XMAX,0);
                        meteorites.push_back(m);
                    }
                }
            }

        }

        SDL_PollEvent(&event); // Récupération des évènements
     
        switch (event.type)
        {
            case SDL_QUIT: // Fin du jeu
                quit = true;
                break;

            case SDL_KEYDOWN: // Relâchement d'une touche
                if ( event.key.keysym.sym == SDLK_LEFT) // Touche Left 
                {
                    if (pers.x >= deplacement){
                        pers.x -= deplacement;
                    }

                    else{
                        pers.x=0;
                    }
                     switch(type)
                    {
                        case (HN):
                            Pers1.set_posx(pers.x);
                            break;
                        case (SH):
                            Pers2.set_posx(pers.x);
                            break;
                        case (EN):
                            Pers3.set_posx(pers.x);
                            break;
                        case (SE):
                            Pers4.set_posx(pers.x);
                            break;            
                    }
                }
                if ( event.key.keysym.sym == SDLK_RIGHT && pers.x<XMAX) // Touche Right
                {
                    if (pers.x <= XMAX-taille_pers - deplacement){
                        pers.x += deplacement;
                    }
                    else{
                        pers.x=XMAX-taille_pers;
                    }
                    switch(type)
                    {
                        case (HN):
                            Pers1.set_posx(pers.x);
                            break;
                        case (SH):
                            Pers2.set_posx(pers.x);
                            break;
                        case (EN):
                            Pers3.set_posx(pers.x);
                            break;
                        case (SE):
                            Pers4.set_posx(pers.x);
                            break;            
                    }
                }
                if ( event.key.keysym.sym == SDLK_UP && (type == SE) && pouvoir == 1) // Touche UP si le pouvoire du SuperET est activé
                {   
                    if (pers.y >= voler){
                        pers.y -= voler;
                    }

                    else{
                        pers.y=0;
                    }
                    switch(type)
                    {
                        case(EN): Pers3.set_posy(pers.y);
                            break;
                        case(SE): Pers4.set_posy(pers.y);
                            break;
                        default : break;
                    }
                }
                if ( event.key.keysym.sym == SDLK_DOWN && (type == SE) && pouvoir == 1) // Touche DOWN si le pouvoire du SuperET est activé
                {
                    if (pers.y <= YMAX-taille_pers - voler){
                        pers.y += voler;
                    }
                    else{
                        pers.y=YMAX-taille_pers;
                    }
                    switch(type)
                    {
                        case(EN): Pers3.set_posy(pers.y);
                            break;
                        case(SE): Pers4.set_posy(pers.y);
                            break;  
                        default : break;          
                    }
                    
                }    
                               
                if ( event.key.keysym.sym == SDLK_a && pouvoir == 0) // Touche A
                {
                    pouvoir = 1;
                    temps_pouvoir = temps;
                    switch (type)
                    {
                        case(SH): Pers2.pouvoir();
                            break;
                        case(SE): if (pouvoir == 1){
                            vitesse = Pers4.pouvoirET(vitesse);
                            }
                            break;
                        default : break;    
                    }
                //break  ; 
                }

            case SDL_MOUSEBUTTONDOWN: // Evènements de la souris 
                SDL_GetMouseState( &mx, &my );
                // Choix mode Humain
                if (mx > Message_rect_humain.x && mx < Message_rect_humain.x + Message_rect_humain.w && my > Message_rect_humain.y && my < Message_rect_humain.y+Message_rect_humain.h && jeu==0){
                    jeu = 1;
                    type = HN;
                    taille_pers = Pers1.get_taille();
                    pers.y = YMAX-taille_pers;
                    pers.w = pers.h = taille_pers;
                    Pers2.set_vie(0);
                    Pers3.set_vie(0);
                    Pers4.set_vie(0);   
                }
                // Choix mode ET
                if (mx > Message_rect_ET.x && mx < Message_rect_ET.x + Message_rect_ET.w && my > Message_rect_ET.y && my < Message_rect_ET.y+Message_rect_ET.h && jeu==0){
                    jeu = 1;
                    type = EN;
                    taille_pers = Pers3.get_taille();
                    pers.y = YMAX-taille_pers;
                    pers.w = pers.h = taille_pers;
                    Pers1.set_vie(0);
                    Pers2.set_vie(0);
                    Pers4.set_vie(0);
                }                
        }
    
        switch(type) // Récupération couleur personnage
        {
            case (HN): SDL_SetRenderDrawColor(renderer, Pers1.get_couleur()[0],Pers1.get_couleur()[1],Pers1.get_couleur()[2],Pers1.get_couleur()[3]); 
                vie = Pers1.get_vie();
                break;
            case (SH): SDL_SetRenderDrawColor(renderer, Pers2.get_couleur()[0],Pers2.get_couleur()[1],Pers2.get_couleur()[2],Pers2.get_couleur()[3]); 
                vie = Pers2.get_vie();
                break;
            case (EN): SDL_SetRenderDrawColor(renderer, Pers3.get_couleur()[0],Pers3.get_couleur()[1],Pers3.get_couleur()[2],Pers3.get_couleur()[3]); 
                vie = Pers3.get_vie();
                break;
            case (SE): SDL_SetRenderDrawColor(renderer, Pers4.get_couleur()[0],Pers4.get_couleur()[1],Pers4.get_couleur()[2],Pers4.get_couleur()[3]); 
                vie = Pers4.get_vie();
                if (vie > 0)
                break;            
        }
        if (vie > 0 && jeu == 1){ // Affichage du personnage
            SDL_RenderFillRect(renderer, &pers);

        }

        else if(jeu == 1) // Affichage de l'image "perdu"
        {
            SDL_Rect dstrect = { static_cast<int>( XMAX/2-100), static_cast<int>(YMAX/2.8), 200, 150 };
            SDL_RenderCopy(renderer, texture_looseGame, NULL, &dstrect);
        }
        

        for (int i=0;i< meteorites.size(); i++)
        {   
            x = meteorites[i].get_posx();
            y = meteorites[i].get_posy();

            if ((y> YMAX) ) // Mise à jour des météorites 
            {
                meteorites.erase(meteorites.begin()+i);
            }
            else
            {
                if (((pers.x - x < taille_met) && (pers.x - x > 0)) || ((x - pers.x < taille_pers) && (x - pers.x > 0)))
                    if ( y > pers.y && y < pers.y + taille_pers)
                    {
                        if (meteorites[i].get_couleur()=="rouge" && ((Pers2.get_bouclier() ==0 && type==SH) || type != SH)) // Action météorites rouges
                        {
                            switch(type)
                            {
                                case (HN): Pers1.set_vie(Pers1.get_vie()-1);
                                    break;
                                case (SH): Pers2.set_vie(Pers2.get_vie()-1);
                                    break;
                                case (EN): Pers3.set_vie(Pers3.get_vie()-1);
                                    break;
                                case (SE): Pers4.set_vie(Pers4.get_vie()-1);
                                    break;            
                            }
                            meteorites.erase(meteorites.begin()+i);
                        }
                        if (meteorites[i].get_couleur()=="vert") // Action météorites vertes
                        {
                            switch(type)
                            {
                                case (HN): Pers1.set_vie(Pers1.get_vie()+1);
                                    break;
                                case (SH): Pers2.set_vie(Pers2.get_vie()+1);
                                    break;
                                case (EN): Pers3.set_vie(Pers3.get_vie()+1);
                                    break;
                                case (SE): Pers4.set_vie(Pers4.get_vie()+1);
                                    break;            
                            }
                            meteorites.erase(meteorites.begin()+i);
                        }
                        if (meteorites[i].get_couleur()=="bleu" && autorisation_pouvoir == 1) // Action météorites bleues
                        {
                            switch(type)
                            {
                                case (HN):  type = SH;
                                    Pers2.set_vie(Pers1.get_vie());
                                    taille_pers = Pers2.get_taille();
                                    pers.w = taille_pers;
                                    pers.h = taille_pers;
                                    pers.y = YMAX - taille_pers;
                                    pouvoir = 0;
                                    autorisation_pouvoir = 0;
                                    break;
                                case (EN): 
                                    type = SE;
                                    Pers4.set_vie(Pers3.get_vie());
                                    taille_pers = Pers4.get_taille();
                                    pers.w = taille_pers;
                                    pers.h = taille_pers;
                                    pers.y = YMAX - taille_pers;
                                    pouvoir = 0;
                                    autorisation_pouvoir = 0;
                                    break;  
                                default: 
                                    pouvoir= 0 ; 
                                    break;
                            }
                            meteorites.erase(meteorites.begin()+i);
                        }
                    }

                if (vie > 0) // Affichage des météorites
                {
                    SDL_Rect rect = { x, y, taille_met, taille_met };
                    meteorites[i].set_posy(y + vitesse);
                    SDL_SetRenderDrawColor(renderer, meteorites[i].get_rect()[0], meteorites[i].get_rect()[1], meteorites[i].get_rect()[2], meteorites[i].get_rect()[3]); 
                    SDL_RenderFillRect(renderer, &rect);
                }
                else{
                    meteorites.clear();
                }
            }
        }
        
        if (pouvoir == 1 && temps_pouvoir+duree_pouvoir > temps) // Temps d'activation du pouvoir
        {
            SDL_Color col = {0, 0, 0};

            char mess[10];
            sprintf(mess, "Pouvoir actif pendant : %d s", (duree_pouvoir+temps_pouvoir-temps)/1000);
            
            SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans2, mess, col);
            SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

            SDL_Rect Message_rect; 
            Message_rect.x = XMAX-200;  
            Message_rect.y = 50; 
            Message_rect.w = surfaceMessage->w; 
            Message_rect.h = surfaceMessage->h; 

            SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
            SDL_DestroyTexture(Message);
            SDL_FreeSurface(surfaceMessage);
        }

        if (pouvoir == 1 && temps_pouvoir+duree_pouvoir < temps){ // Fin de pouvoir
            pers.y = YMAX-taille_pers;
            if(type == SE){
                vitesse = Pers4.fin_pouvoirET(vitesse);
                type = EN;
                Pers3.set_vie(Pers4.get_vie());
                taille_pers = Pers3.get_taille();
                pers.w = taille_pers;
                pers.h = taille_pers;
                pers.y = YMAX - taille_pers;
            }
            if(type == SH){
                type = HN;
                Pers2.fin_pouvoir();
                Pers1.set_vie(Pers2.get_vie());
                taille_pers = Pers1.get_taille();
                pers.w = taille_pers;
                pers.h = taille_pers;
                pers.y = YMAX - taille_pers;

            }

            if (temps_pouvoir + duree_pouvoir + delai_activation_pouvoir > temps && vie > 0){ // Délai de récupération du pouvoir
            SDL_Color col = {0, 0, 0};

            char mess[10];
            sprintf(mess, "Prochain pouvoir dans : %d s", (duree_pouvoir + temps_pouvoir + delai_activation_pouvoir - temps)/1000);
            
            SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans2, mess, col);
            SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

            SDL_Rect Message_rect; 
            Message_rect.x = XMAX-250;  
            Message_rect.y = 50; 
            Message_rect.w = surfaceMessage->w; 
            Message_rect.h = surfaceMessage->h; 
            SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
            SDL_DestroyTexture(Message);
            SDL_FreeSurface(surfaceMessage);

            }
            else{
                pouvoir = -1;
                autorisation_pouvoir = 1;
            }
        }
        
        temps = SDL_GetTicks(); // Variable temps

        SDL_RenderPresent(renderer); // Affichage de la fenêtre

    }
     
    // nettoyage SDL
    SDL_DestroyTexture(texture_looseGame);
    SDL_FreeSurface(looseGame);
     
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


     
    return 0;
}