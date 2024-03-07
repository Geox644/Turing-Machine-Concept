/* GRIGOREANU Andreea-Georgiana - 313CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

/* definire lista dublu inlantuita cu santinela */
typedef struct celula2
{
  char info;              
  struct celula2 *pre, *urm;
} TCelula2, *TLista2;

typedef struct banda_magica
{
    TLista2 lista;  // Pointer catre inceputul listei dublu inlantuite (santinela)
    TLista2 deget;  // Pointer catre pozitia curenta în lista (degetul)
} TBandaMagica;

/* COADA */
typedef struct celula
{
  char *comanda, parametru;
  struct celula* urm;
} TCelula, *TLista;

typedef struct coada
{
  TLista inc, sf;  // adresa primei si ultimei celule
} TCoada;

/* STIVA */
typedef struct celst
{
void *adresa;
struct celst *urm;
} TCelulaStiva, *TStiva;

TLista2 InitSantinela();
TLista2 InitLista();
TBandaMagica *InitBandaMagica();
void AfiseazaBanda(TBandaMagica *banda, FILE *file);
void AfiseazaElemCurent(TBandaMagica *banda, FILE *file);
void DistrugeBanda(TBandaMagica *banda);

/* FUNCTII UPDATE */
void MutaDreapta(TBandaMagica *banda);
void MutaStanga(TBandaMagica *banda);
void ScrieCaracter(TBandaMagica *banda, char caracter);
void MutareStangaCaracter(TBandaMagica *banda, char caracter, FILE *file);
void MutareDreaptaCaracter(TBandaMagica *banda, char caracter);
void InserareStanga(TBandaMagica *banda, char caracter, FILE *file);
void InserareDreapta(TBandaMagica *banda, char caracter);

/* FUNCTII COADA */
TLista create_celula(char *x, char y);
void init_coada(TCoada *c);
void enqueue(TCoada *c, char *x, char y);
TLista Dequeue(TCoada* c);
void DistrQ(TCoada *c);
// void afisare_coada(TCoada *c); 

/* FUNCTII STIVA  */
TStiva InitS(void);
void Push(TStiva* vf, void* x);
void* Pop(TStiva* vf);
void DistrugeS(TStiva* vf);
// void AfisareStiva(TStiva vf);
