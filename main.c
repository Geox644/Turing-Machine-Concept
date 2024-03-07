/* GRIGOREANU Andreea-Georgiana - 313CB */
#include "tema1.h"

int main()
{
    TBandaMagica* banda = InitBandaMagica();
    TCoada queue;
    init_coada(&queue);
    TStiva undo = InitS();
    TStiva redo = InitS();

    FILE* in_file = fopen("tema1.in", "r");
    FILE* out_file = fopen("tema1.out", "w");

    int nr_comenzi = 0;
    fscanf(in_file, "%d", &nr_comenzi);
    fgetc(in_file); // citeste si ignora caracterul newline dupa numarul de
                    // comenzi

    // adaugarea comenzilor in coada
    int i;
    for (i = 0; i < nr_comenzi; i++) {
        char line[MAX_LENGTH];
        fgets(line, sizeof(line), in_file); // citeste intregul rand

        char comanda[MAX_LENGTH];
        char parametru = 0;

        // extrage comanda folosind strtok
        char* token = strtok(line, " \n");
        if (token != NULL) {
            strcpy(comanda, token);
        }

        // extrage parametrul, daca exista
        token = strtok(NULL, " ");
        if (token != NULL) {
            parametru = token[0];
        }

        if (strcmp(comanda, "MOVE_LEFT") == 0) {
            enqueue(&queue, comanda, parametru);
        } else if (strcmp(comanda, "MOVE_RIGHT") == 0) {
            enqueue(&queue, comanda, parametru);
        } else if (strcmp(comanda, "WRITE") == 0) {
            enqueue(&queue, comanda, parametru);
        } else if (strcmp(comanda, "MOVE_LEFT_CHAR") == 0) {
            enqueue(&queue, comanda, parametru);
        } else if (strcmp(comanda, "MOVE_RIGHT_CHAR") == 0) {
            enqueue(&queue, comanda, parametru);
        } else if (strcmp(comanda, "INSERT_LEFT") == 0) {
            enqueue(&queue, comanda, parametru);
        } else if (strcmp(comanda, "INSERT_RIGHT") == 0) {
            enqueue(&queue, comanda, parametru);
        } else if (strcmp(comanda, "EXECUTE") == 0) {
            TLista temp  = Dequeue(&queue); // prima comanda din coada
            if (strcmp(temp->comanda, "MOVE_LEFT") == 0) {
                if (banda->deget != banda->lista->urm) {
                    Push(&undo, banda->deget);
                }
                MutaStanga(banda);
            } else if (strcmp(temp->comanda, "MOVE_RIGHT") == 0) {
                Push(&undo, banda->deget);
                MutaDreapta(banda);
            } else if (strcmp(temp->comanda, "WRITE") == 0) {
                ScrieCaracter(banda, temp->parametru);
                DistrugeS(&redo);
                DistrugeS(&undo);
            } else if (strcmp(temp->comanda, "MOVE_LEFT_CHAR") == 0) {
                MutareStangaCaracter(banda, temp ->parametru, out_file);
                DistrugeS(&redo);
                DistrugeS(&undo);
            } else if (strcmp(temp->comanda, "MOVE_RIGHT_CHAR") == 0) {
                MutareDreaptaCaracter(banda, temp ->parametru);
                DistrugeS(&redo);
                DistrugeS(&undo);
            } else if (strcmp(temp->comanda, "INSERT_LEFT") == 0) {
                InserareStanga(banda, temp->parametru, out_file);
                DistrugeS(&redo);
                DistrugeS(&undo);
            } else if (strcmp(temp->comanda, "INSERT_RIGHT") == 0) {
                InserareDreapta(banda, temp->parametru);
                DistrugeS(&redo);
                DistrugeS(&undo);
            }
            free(temp->comanda);
            free(temp );
        } else if (strcmp(comanda, "SHOW") == 0) {
            AfiseazaBanda(banda, out_file);
        } else if (strcmp(comanda, "SHOW_CURRENT") == 0) {
            AfiseazaElemCurent(banda, out_file);
        } else if (strcmp(comanda, "UNDO") == 0) {
            Push(&redo, banda->deget); // pun in redo adresa degetului
            TLista2 old_address = (TLista2)Pop(&undo);
            if (old_address != NULL) {
                banda->deget = old_address;
            }
        } else if (strcmp(comanda, "REDO") == 0) {
            Push(&undo, banda->deget);
            TLista2 old_address = (TLista2)Pop(&redo);
            if (old_address != NULL) {
                banda->deget = old_address;
            }
        }
    }
    fclose(in_file);
    fclose(out_file);
    DistrQ(&queue);
    DistrugeS(&undo);
    DistrugeS(&redo);
    DistrugeBanda(banda);

    return 0;
}
