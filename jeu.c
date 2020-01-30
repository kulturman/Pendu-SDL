/*
* \
* * contient les fonctions gerant une partie du jeu
* *
* *
*/

#include "includes.h"

void launchGame(SDL_Surface *ecran)
{

    srand(time(NULL));
    int nombreDeCoups = 8 , i , gagne = 0 , tempsActuel , tempsPrecedent;
    size_t tailleMot;
    TTF_Font *police = TTF_OpenFont("GenBasB.ttf" , 24);
    SDL_Surface *surfaceJeu = NULL , *image[9] = {NULL} , *imageActuelle = NULL , *texte = NULL;
    SDL_Rect positionImage , positionSurfaceJeu , positionTexte;
    SDL_Color couleurBleue = {0 , 0 , 255};
    SDL_Color couleurRouge = {200 , 0 , 0};
    positionSurfaceJeu.x = 0;
    positionSurfaceJeu.y = 0;
    char cheminActuel[100] = " " , motMystere[26] = " " , copieMotMystere[26] = " " , choix;
    char message[100] = " ";
    choisirMot(motMystere);
    tailleMot = strlen(motMystere);
    /* chargement du son*/
    Mix_Chunk *son = Mix_LoadWAV("cri.wav");
    if(!son)
    {
        fprintf(stderr , "Le fichier cri.wav est introuvable");
        exit(EXIT_FAILURE);
    }

    /* initialisation de la copie avec des asterisques*/
    for(i = 0 ; i <= tailleMot - 2 ; i++)
        copieMotMystere[i] = '*';

    copieMotMystere[tailleMot - 1] = '\0';
    motMystere[tailleMot - 1] = '\0'; // on vire le caractere '\n' introduit par fgets

    /* chargement des sprites*/
    for(i = 0; i <= 8 ; i++)
    {
        sprintf(cheminActuel , "sprites//pendu_%d.bmp",i);
        image[i] = IMG_Load(cheminActuel);
    }
    surfaceJeu = SDL_CreateRGBSurface(SDL_HWSURFACE , LARGEUR_FENETRE/2 , HAUTEUR_FENETRE , 32 , 0 , 0 , 0 , 0);
    SDL_FillRect(ecran , NULL , SDL_MapRGB(ecran->format , 255 , 255 , 255));
    SDL_FillRect(surfaceJeu , NULL , SDL_MapRGB(ecran->format , 200 , 200 , 200));
    texte = TTF_RenderText_Blended(police , "TROUVEZ LE MOT MYSTERE" , couleurBleue);
    positionTexte.x = (LARGEUR_FENETRE)/4 - (texte->w)/2;
    positionTexte.y = 0;
    positionImage.x = LARGEUR_FENETRE - image[0]->w ;
    positionImage.y = 0;

    do
    {
        SDL_FillRect(ecran , NULL , SDL_MapRGB(ecran->format , 255 , 255 , 255));
        SDL_FillRect(surfaceJeu , NULL , SDL_MapRGB(ecran->format , 200 , 200 , 200));
        imageActuelle = image[nombreDeCoups];
        SDL_BlitSurface(surfaceJeu , NULL , ecran , &positionSurfaceJeu);
        SDL_BlitSurface(imageActuelle , NULL , ecran , &positionImage);
        SDL_BlitSurface(texte , NULL , ecran , &positionTexte);
        devoilerMot(ecran , motMystere , tailleMot - 1 , copieMotMystere);
        SDL_Flip(ecran);
        choix = toupper(proposition());
        if(!aTrouve(choix , motMystere , tailleMot - 1 , copieMotMystere))
            nombreDeCoups--;
        if(!strncmp(motMystere , copieMotMystere , tailleMot - 1))
            gagne = 1;

    } while(!gagne && nombreDeCoups > 0);

    if(!nombreDeCoups)
    {
        SDL_FillRect(ecran , NULL , SDL_MapRGB(ecran->format , 255 , 255 , 255));
        SDL_FillRect(surfaceJeu , NULL , SDL_MapRGB(ecran->format , 200 , 200 , 200));
        imageActuelle = image[nombreDeCoups];
        SDL_BlitSurface(surfaceJeu , NULL , ecran , &positionSurfaceJeu);
        SDL_BlitSurface(imageActuelle , NULL , ecran , &positionImage);
        SDL_BlitSurface(texte , NULL , ecran , &positionTexte);
        devoilerMot(ecran , motMystere , tailleMot - 1 , copieMotMystere);
    }

    if(gagne)
    {
        sprintf(message , "BRAVO LE MOT MYSTERE ETAIT BIEN %s",motMystere);

    }

    else
    {
        Mix_PlayChannel(-1 , son , 0);
        sprintf(message , "PERDU LE MOT MYSTERE ETAIT %s ",motMystere);
    }

    texte = TTF_RenderText_Blended(police , message , couleurRouge);
    positionTexte.x = (LARGEUR_FENETRE)/2 - (texte->w)/2;
    positionTexte.y = (HAUTEUR_FENETRE)/2 - (texte->h)/2;
    SDL_BlitSurface(texte , NULL , ecran , &positionTexte);
    SDL_Flip(ecran);

    tempsActuel = tempsPrecedent = SDL_GetTicks();

    while(1)
    {
        tempsActuel = SDL_GetTicks();
        if((tempsActuel - tempsPrecedent) >= LAPS_DE_TEMPS)
            break;
        else
            SDL_Delay(LAPS_DE_TEMPS - tempsActuel + tempsPrecedent);
    }

    for(i = 0; i <= 8 ; i++)
        SDL_FreeSurface(image[i]);
    TTF_CloseFont(police);
    SDL_FreeSurface(texte);
    SDL_FreeSurface(surfaceJeu);

}


void devoilerMot(SDL_Surface *ecran , char *motSecret, size_t longueurMot , char *copieMot)
{
    SDL_Color couleurBleue = {0 , 0 , 255};
    SDL_Rect positionMot;
    SDL_Surface *surfaceMot = NULL;
    TTF_Font *police = TTF_OpenFont("GenBasB.ttf" , 24);
    surfaceMot = TTF_RenderText_Blended(police , copieMot , couleurBleue);
    positionMot.x = (LARGEUR_FENETRE)/4 - (surfaceMot->w)/2;;
    positionMot.y = 100;
    SDL_BlitSurface(surfaceMot , NULL , ecran , &positionMot);
    SDL_Flip(ecran);
    SDL_FreeSurface(surfaceMot);
    TTF_CloseFont(police);
}


int aTrouve(char c , char *motSecret , size_t longueurMot , char *copieMot)
{
    int trouve = FAUX , i;
    for(i = 0 ; i < longueurMot ; i++)
    {
        if(c == motSecret[i])
        {
            trouve = VRAI;
            copieMot[i] = c;

        }

    }

    return trouve;
}



char proposition()
{
    SDL_Event event;
    char choix ;
    while(1)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {

            case SDL_QUIT:
                exit(EXIT_FAILURE);
                break;

            case SDL_KEYDOWN:
                choix = event.key.keysym.sym;
                franciserClavier(&choix);
                return choix;

        }
    }

}


void franciserClavier(char *c)
{
    switch(*c)
    {
        case ';':
           *c = 'm';
           break;

        case  'a':
            *c = 'q';
            break;

        case 'q':
            *c = 'a';
    }
}
