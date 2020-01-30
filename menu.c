#include "includes.h"

void displayMenu(SDL_Surface *ecran , SDL_Rect positionPointeur)
{

    /* on cree les surfaces pour les texte et pour la portion où se déroule la partie*/
    SDL_Surface *texte[3] = {NULL} , *pointeur = NULL;
    SDL_Color couleurNoire = {0 , 0 , 0};
    SDL_Rect position , positionTitre;
    positionTitre.x = 310;
    positionTitre.y = 20;
    TTF_Font *police = TTF_OpenFont("GenBasB.ttf" , 24);
    TTF_Font *policeTitre = TTF_OpenFont("police.ttf" , 30);
    pointeur = IMG_Load("sprites//pointeur.bmp");
    int i ;
    if(!police || !policeTitre)
    {
        fprintf(stderr , "les fichiers GenBasB et/ou police sont absentes");
        exit(EXIT_FAILURE);
    }

    /* je rends l'arriere fond du pointeur transparent */
    SDL_SetColorKey(pointeur , SDL_SRCCOLORKEY , SDL_MapRGB(ecran->format , 255 , 255 , 255));

    texte[TITRE] = TTF_RenderText_Blended(policeTitre , "PENDU" , couleurNoire);
    texte[JOUER] = TTF_RenderText_Blended(police , " JOUER" , couleurNoire);
    texte[QUITTER] = TTF_RenderText_Blended(police , " QUITTER" , couleurNoire);
    Uint32 couleurJaune = SDL_MapRGB(ecran->format , 255 , 255 , 210);

    SDL_FillRect(ecran , NULL , couleurJaune);
    position.y = 150;
    for(i = 1 ; i <= 2 ; i++)
    {
        position.x = (LARGEUR_FENETRE)/2 - (texte[0]->w)/2;
        SDL_BlitSurface(texte[i] , NULL , ecran , &position);
        position.y += INTERVALLE;
    }

    SDL_BlitSurface(pointeur , NULL , ecran , &positionPointeur);
    SDL_BlitSurface(texte[TITRE] , NULL , ecran , &positionTitre);
    SDL_Flip(ecran);

    /* liberation des surfaces */
    SDL_FreeSurface(pointeur);
    for(i = 0 ; i <= 2 ; i++)
        SDL_FreeSurface(texte[i]);
    TTF_CloseFont(police);
    TTF_CloseFont(policeTitre);

}
