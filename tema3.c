#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nod { //creare structura pentru un nod din graf
    int nr;
    char denumire[30];
    struct muchie *edges;
} nod;

typedef struct muchie { //creare structura pentru o muchie
    struct nod *dest;
    int cost;
    struct muchie *next;
} muchie;

void DFS(int node, int viz[], nod oras[]) { //functie pentru parcurgerea in 
//adancime a grafului
    viz[node] = 1; //nodul de inceput este vizitat
    muchie *edge = oras[node].edges;
    while (edge != NULL) {
        int vecin;
        vecin = edge->dest->nr;
        if (viz[vecin] == 0) {  //daca vecinul este nevizitat apelez recursiv 
                                //functia
            DFS(vecin, viz, oras);
        }
        edge = edge->next; //trec la urmatorul vecin
    }
}

int numar_grafuri(nod oras[], int nr_noduri) {
    int viz[nr_noduri]; //vecotorul cu noduri vizitate
    int i;
    for (i = 0; i < nr_noduri; i++) { //initializez vectorul cu 0
        viz[i] = 0;
    }
    int numar_grafuri = 0; //numarul de grafuri este la inceput 0

    for (i = 0; i < nr_noduri; i++) {
        if (viz[i] == 0) { //daca un nod este nevizitat apelez functia 
            DFS(i, viz, oras);
            numar_grafuri++; //maresc numarul de grafuri
        }
    }
    return numar_grafuri; //returnez numarul de grafuri
}

int prim(nod oras[], int nr_noduri, int start) {
    int distanta[nr_noduri];
    int predecesor[nr_noduri];
    int vizitat[nr_noduri];
    int i;
    for (i = 0; i < nr_noduri; i++) {
        distanta[i] = 999; //initialiez variabilele
        predecesor[i] = -1;
        vizitat[i] = 0;
    }
    distanta[start] = 0; //distanta de inceput este 0

    while (1) {
        int minDistanta = 999;
        int u = -1;

        for (i = 0; i < nr_noduri; i++) { //parcurg fiecare nod
            if (vizitat[i] == 0 && distanta[i] < minDistanta) {
                //gasesc nod nevizitat cu cea mai mica distanta
                minDistanta = distanta[i]; //modific distanta minima
                u = i;
            }
        }
        if (u == -1) { //nu exista noduri nevizitate
            break;
        }
        vizitat[u] = 1; //marchez nodul ca vizitat
        muchie *edge = oras[u].edges;
        while (edge != NULL) {
            int v = edge->dest->nr; //vecinul nodului curent
            int cost = edge->cost;

            if (vizitat[v] == 0 && cost < distanta[v]) {
                //verific daca vecinul este vizitat si daca costul este mai mic 
                //decat distanta
                distanta[v] = cost;
                predecesor[v] = u;
            }
            edge = edge->next; //trec la urmatorul vecin
        }
    }

    int costMinim = 0;
    for (i = 0; i < nr_noduri; i++) {
        if (predecesor[i] != -1) {
            costMinim += distanta[i]; //aflu costul minim pentru o componenta 
                                      //conexa
        }
    }
    return costMinim; //returnez costul minim
}

void bubbleSort(int cost[], int size) {
    int i, j;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (cost[j] > cost[j + 1]) {
                //schimb elementele intre ele
                int temp = cost[j];
                cost[j] = cost[j + 1];
                cost[j + 1] = temp;
            } //vectorul cost este sortat
        }
    }
}

void primCostMinim(nod oras[], int nr_noduri, int nr_grafuri, FILE *fp) {
    int viz[nr_noduri];
    int i;
    for (i = 0; i < nr_noduri; i++) {
        viz[i] = 0; //nodurile sunt nevizitate
    }
    int numar_grafuri = 0; //nu exista componente conexe

    int cost[nr_grafuri];
    for (i = 0; i < nr_grafuri; i++) {
        cost[i] = 0; //costul pentru fiecare componenta este 0
    }

    for (i = 0; i < nr_noduri; i++) {
        if (viz[i] == 0) { //daca nodul nu a fost vizitat
            DFS(i, viz, oras); //parcurg in adancime
            numar_grafuri++; //incrementez numarul de grafuri
            cost[numar_grafuri - 1] = prim(oras, nr_noduri, i); 
            //adaug costul minim in vector
        }
    }
    bubbleSort(cost, numar_grafuri); //ordonez crescator vectorul
    for (i = 0; i < nr_grafuri; i++) {
        fprintf(fp, "%d\n", cost[i]); //scriu in fisier costurile minime
    } 
}

int main(int argc, char *argv[]) {
    char *cerinta;
    cerinta = argv[1]; //cerinta este argument

    FILE *f;
    f = fopen("tema3.in", "r"); //deschid fisierul 
    int nr_noduri;
    fscanf(f, "%d", &nr_noduri); //citesc numarul de noduri si de muchii
    int nr_muchii;
    fscanf(f, "%d", &nr_muchii);

    nod oras[nr_noduri]; //initializez vectorul de structuri de tip nod

    int i;
    for (i = 0; i < nr_noduri; i++) {
        oras[i].edges = NULL; //initializez muchiile cu NULL
    }

    int j, nod = 0;
    for (i = 0; i < nr_muchii; i++) {
        char nod1[30];
        char nod2[30];
        int nr;
        fscanf(f, "%s %s %d", nod1, nod2, &nr); //citesc nodurile si costul 

        int nod1_nr = -1, nod2_nr = -1;
        for (j = 0; j < nod; j++) { //verific daca nodul este in vector sau nu
            if (strcmp(oras[j].denumire, nod1) == 0) {
                nod1_nr = oras[j].nr; //daca da, atunci modific variabila cu 
                                      //nr nodului
            }
            if (strcmp(oras[j].denumire, nod2) == 0) {
                nod2_nr = oras[j].nr;
            }
        }
        if (nod1_nr == -1) { //daca nu, atunci adaug nodul in vector
            strcpy(oras[nod].denumire, nod1);
            oras[nod].nr = nod;
            nod1_nr = nod;
            nod++; //iterez nr nodurilor
        }

        if (nod2_nr == -1) {
            strcpy(oras[nod].denumire, nod2);
            oras[nod].nr = nod;
            nod2_nr = nod;
            nod++;
        }
        //creez o noua muchie si o adaug in lista de vecini pentru nodul 1
        muchie *edge1 = (muchie *) malloc(sizeof(muchie));
        edge1->dest = &oras[nod2_nr];
        edge1->cost = nr;
        edge1->next = oras[nod1_nr].edges;
        oras[nod1_nr].edges = edge1;

        //creez o noua muchie si o adaug in lista de vecini pentru nodul 2
        muchie *edge2 = (muchie *) malloc(sizeof(muchie));
        edge2->dest = &oras[nod1_nr];
        edge2->cost = nr;
        edge2->next = oras[nod2_nr].edges;
        oras[nod2_nr].edges = edge2;
    }
    fclose(f); //inchid fisierul

    int nr_grafuri;
    nr_grafuri = numar_grafuri(oras, nr_noduri); //apelez functia

    FILE *fp;
    fp = fopen("tema3.out", "w");
    fprintf(fp, "%d\n", nr_grafuri); //scriu in fisier nr de grafuri
    primCostMinim(oras, nr_noduri, nr_grafuri, fp);
    fclose(fp); //inchid fisierul

    return 0;
}
