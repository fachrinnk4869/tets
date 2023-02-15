#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct{
    char a;
    int visited;
}dataSimpul;

typedef struct{
    int b;
}dataJalur;

typedef struct{
    char path[100];
    int jarak;
    int path_index;
}dataPath;

typedef struct smp{
    dataSimpul kontainer;
    struct smp* next;
    struct jlr* first_jalur;
}simpul;

typedef struct jlr{
    dataJalur kontainer_jalur;
    struct jlr* next_jalur;
    simpul *tujuan;
}jalur;

typedef struct elmt{
    dataSimpul kontainer;
    struct elmt* next;
}elemen;

typedef struct{
    elemen* first;
}list;

typedef struct{
    simpul* first;
}graph;

void createEmpty(graph *G);
void addSimpul(dataSimpul inputSimpul, graph *G);
void addJalur(simpul *awal, simpul *tujuan, dataJalur beban);
simpul* findSimpul(dataSimpul inputSimpul, graph G);
void delJalur(dataSimpul ctujuan, simpul *awal);
void delAll(simpul *awal);
void delSimpul(dataSimpul inputSimpul, graph *G);
void printGraph(graph G);
void findRoute(simpul *awal, simpul *tujuan, dataPath curPath, dataPath *maxPath, int path_index, int jarak);