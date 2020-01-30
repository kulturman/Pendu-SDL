/*
* *
* * PAR KULTURM@N DEBUTE LE 05/04/2013 terminé le 08/04/2013
* * DERNIERES MODIFICATIONS EFFECTUEES LE 12/05/2013:ajout du son
* *
*/

#include "includes.h"

int main(int argc , char **argv)
{

    int stop = 0 , choixCourant = 1;
    SDL_Surface *ecran = NULL;
    SDL_Event event;
    SDL_Rect positionPointeur;
    positionPointeur.x = 250;
    positionPointeur.y = 150;
    TTF_Init();

    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == - 1)
    {
        fprintf(stderr ,"L'erreur suivante suivante s'est produite : %s" , SDL_GetError());
        exit(EXIT_FAILURE);
    }
    /* initialisation de SDL_mixer*/
    Mix_Init(MIX_INIT_OGG | MIX_INIT_MOD);
    Mix_OpenAudio(44100 , MIX_DEFAULT_FORMAT , 2 , 1024);
    SDL_WM_SetCaption("LE PENDU" , NULL);
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE , HAUTEUR_FENETRE , 32 , SDL_HWSURFACE | SDL_DOUBLEBUF);
    if(!ecran)
        exit(EXIT_FAILURE);

    /* creation des differentes couleurs */
    Uint32 couleurJaune = SDL_MapRGB(ecran->format , 255 , 255 , 210);
    while(!stop)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                stop = 1;
                break;

            case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {

                case SDLK_UP:
                    if(--choixCourant < 1)
                    {
                        choixCourant = 1;
                    }

                    else
                    {
                        positionPointeur.y -= INTERVALLE;
                    }

                    break;


                case SDLK_DOWN:
                    if(++choixCourant > 2)
                    {
                        choixCourant = 2;
                    }

                    else
                    {
                        positionPointeur.y += INTERVALLE;
                    }

                    break;

                case SDLK_RETURN:
                    if(choixCourant == QUITTER)
                        stop = 1;

                    else
                        launchGame(ecran);
                    break;

                default:
                    break;

                }


        }

        SDL_FillRect(ecran , NULL , couleurJaune);
        displayMenu(ecran , positionPointeur);
        SDL_Flip(ecran);
    }

    SDL_Quit();
    TTF_Quit();
    return 0;
}
