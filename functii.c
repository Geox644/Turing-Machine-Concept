/* GRIGOREANU Andreea-Georgiana - 313CB */
#include "tema1.h"

/* initializare santinela */
TLista2 InitSantinela()
{
    TLista2 santinela = (TLista2)malloc(sizeof(TCelula2));
    if (!santinela) {
        return NULL;
    }
    santinela->info = 0;
    santinela->pre = NULL;
    santinela->urm = NULL;
    return santinela;
}

/* initializare lista dubla inlatuita */
TLista2 InitLista()
{
    TLista2 primulElement = (TLista2)malloc(sizeof(TCelula2));
    primulElement->info = '#';
    primulElement->pre = NULL;
    primulElement->urm = NULL;
    return primulElement;
}

TBandaMagica* InitBandaMagica()
{
    TBandaMagica* banda = (TBandaMagica*)malloc(sizeof(TBandaMagica));

    // initializam santinela si primul nod al listei
    TLista2 santinela = InitSantinela();
    TLista2 primulElement = InitLista();

    // setam pointerul 'lista' al structurii 'TBandaMagica' sa indice santinela
    banda->lista = santinela;

    // setam 'degetul' sa indice primul element din lista
    banda->deget = primulElement;

    // setam pointerii pre si urm pentru primul element si santinela
    santinela->urm = primulElement;
    primulElement->pre = santinela;

    return banda;
}

/* SHOW */
void AfiseazaBanda(TBandaMagica* banda, FILE* file)
{
    TLista2 pozitieCurenta = banda->lista->urm;

    while (pozitieCurenta != NULL) {
        if (pozitieCurenta == banda->deget) {
            fprintf(file, "|%c|", pozitieCurenta->info);
        } else {
            fprintf(file, "%c", pozitieCurenta->info);
        }
        pozitieCurenta = pozitieCurenta->urm;
    }
    fprintf(file, "\n");
}

/* SHOW_CURRENT */
void AfiseazaElemCurent(TBandaMagica* banda, FILE* file)
{
    fprintf(file, "%c\n", banda->deget->info);
}

/* distrugere lista */
void DistrugeBanda(TBandaMagica* banda)
{
    TLista2 pozitieCurenta = banda->lista;
    TLista2 element_urmator;

    while (pozitieCurenta != NULL) {
        element_urmator
            = pozitieCurenta->urm; // Salvam pointerul catre urmatorul element
        free(
            pozitieCurenta); // Eliberam memoria alocata pentru elementul curent
        pozitieCurenta = element_urmator; // Ne deplasăm la următorul element
    }
    banda->lista = NULL;
    banda->deget = NULL;

    free(banda);
}

/* FUNCTII UPDATE */

void MutaDreapta(TBandaMagica* banda)
{
    if (banda->deget->urm == NULL) { // verific daca exista element in dreapta
        // Adaugam un nod nou la dreapta cu caracterul "#"
        TLista2 elementNou = (TLista2)malloc(sizeof(TCelula2));
        elementNou->info = '#';
        elementNou->pre = banda->deget;
        elementNou->urm = NULL;
        banda->deget->urm = elementNou;
        banda->deget = elementNou;
    } else {
        // Mutam poziția degetului la dreapta
        banda->deget = banda->deget->urm;
    }
}

void MutaStanga(TBandaMagica* banda)
{
    if (banda->deget->pre != banda->lista) { // banda->deget !=
                                             // banda->lista->urm
        banda->deget = banda->deget->pre;
    }
}

void ScrieCaracter(TBandaMagica* banda, char caracter)
{
    banda->deget->info = caracter;
}

void MutareStangaCaracter(TBandaMagica* banda, char caracter, FILE* file)
{
    if (banda->deget->info == caracter)
        return;
    TLista2 aux = banda->deget;
    while (banda->deget != banda->lista->urm) {
        banda->deget = banda->deget->pre;
        if (banda->deget->info == caracter) {
            return;
        }
    }
    banda->deget = aux;
    fprintf(file, "ERROR\n");
}

void MutareDreaptaCaracter(TBandaMagica* banda, char caracter)
{
    if (banda->deget->info == caracter)
        return;
    while (banda->deget->urm != NULL) {
        banda->deget = banda->deget->urm;
        if (banda->deget->info == caracter) {
            return;
        }
    }
    // am ajuns la ultimul element al benzii
    TLista2 elementNou = (TLista2)malloc(sizeof(TCelula2));
    elementNou->info = '#';
    elementNou->pre = banda->deget;
    elementNou->urm = NULL;
    banda->deget->urm = elementNou;
    banda->deget = elementNou;
}

void InserareStanga(TBandaMagica* banda, char caracter, FILE* file)
{
    if (banda->deget->pre == banda->lista) {
        fprintf(file, "ERROR\n");
        return;
    }
    TLista2 elementNou = (TLista2)malloc(sizeof(TCelula2));
    elementNou->info = caracter;
    elementNou->pre = banda->deget->pre;
    elementNou->urm = banda->deget;
    // elementul nou devine urmatorul element al elementului din stanga
    // degetului
    banda->deget->pre->urm = elementNou; // elementul din stanga degetului
    // elementul nou devine elementul din stanga degetului
    banda->deget->pre = elementNou;
    // degetul se muta la stanga pe elementul nou inserat
    banda->deget = elementNou;
}

void InserareDreapta(TBandaMagica* banda, char caracter)
{
    TLista2 elementNou = (TLista2)malloc(sizeof(TCelula2));
    elementNou->info = caracter;
    elementNou->pre = banda->deget;
    elementNou->urm = banda->deget->urm;
    // actualizeaza pointerii din lista
    if (banda->deget->urm != NULL) {
        banda->deget->urm->pre = elementNou;
    }
    banda->deget->urm = elementNou;
    // muta degetul pe noul element
    banda->deget = elementNou;
}

/* FUNCTII COADA */

/* initializarea cozii */
void init_coada(TCoada* c)
{
    c->inc = NULL;
    c->sf = NULL;
}

/* crearea unui nod nou pentru coada */
TLista create_celula(char* x, char y)
{
    TLista aux = (TLista)malloc(sizeof(TCelula));
    aux->comanda = (char*)malloc((strlen(x) + 1) * sizeof(char));
    strcpy(aux->comanda, x);
    aux->parametru = y;
    aux->urm = NULL;
    return aux;
}

/* adauga nod in coada */
void enqueue(TCoada* c, char* x, char y)
{ // x - sir de carctere, y - un caracter
    TLista aux = create_celula(x, y);

    if (c->sf == NULL) {
        c->inc = c->sf = aux;
        return;
    }

    c->sf->urm = aux;
    c->sf = aux;
}

/* extrage primul element din coada */
TLista Dequeue(TCoada* c)
{

    TLista p = c->inc;
    c->inc = p->urm;
    if (c->inc == NULL) {
        c->sf = NULL;
    }

    return p;
}

/* eliberare coada */
void DistrQ(TCoada* c)
{
    while (c->inc != NULL) {
        TLista aux = c->inc;
        c->inc = aux->urm;
        free(aux->comanda);
        free(aux);
    }
    c->sf = NULL;
}

/* FUNCTII STIVA */

/* initializare stiva */
TStiva InitS(void) { return NULL; }

/* adaugare element stiva */
void Push(TStiva* vf, void* x)
{
    TStiva aux = (TStiva)malloc(sizeof(TCelulaStiva));
    if (!aux)
        return;
    aux->adresa = x;
    aux->urm = *vf;
    *vf = aux;
}

/* extragere element stiva */
void* Pop(TStiva* vf)
{
    if (*vf == NULL)
        return NULL;
    void* value = (*vf)->adresa;
    TStiva aux = *vf;
    *vf = aux->urm;
    free(aux);
    return value;
}

/* distruge stiva */
void DistrugeS(TStiva* vf)
{
    TStiva aux;
    while (*vf) {
        aux = *vf;
        *vf = (*vf)->urm;
        free(aux);
    }
}

/* afisari pentru verificare */

// void AfiseazaBanda(TBandaMagica banda) {
//     TLista2 pozitieCurenta = banda.lista->urm;
//     while (pozitieCurenta != NULL) {
//         if (pozitieCurenta == banda.deget) {
//             printf("|%c|", pozitieCurenta->info);
//         } else if (pozitieCurenta != banda.lista) {
//             printf("%c", pozitieCurenta->info);
//         }
//         pozitieCurenta = pozitieCurenta->urm;
//     }
//     printf("\n");
// }

// void afisare_coada(TCoada *c) {
//     printf("Coada: ");
//     TLista aux = c->inc;
//     while (aux != NULL) {
//         printf("(%s, %c) -> ", aux->comanda, aux->parametru);
//         aux = aux->urm;
//     }
//     printf("NULL\n");
// }

// void AfisareStiva(TStiva vf) {
//     printf("Stiva: ");
//     while (vf != NULL) {
//         printf("%p ", vf->adresa);
//         vf = vf->urm;
//     }
//     printf("\n");
// }
