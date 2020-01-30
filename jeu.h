#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

void launchGame(SDL_Surface *ecran);
void devoilerMot(SDL_Surface *ecran , char *motSecret, size_t longueurMot , char *copieMot);
int aTrouve(char c , char *motSecret , size_t longueurMot , char *copieMot);
char proposition();
void franciserClavier(char *c);
#endif // JEU_H_INCLUDED
