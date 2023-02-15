#include"header.h"

int main(){

    graph G;
    dataSimpul inputSimpul;
    dataJalur inputJalur;

    createEmpty(&G);
    int n;
    scanf("%d", &n);
    for(int i = 0;i<n;i++){
        scanf(" %c", &inputSimpul.a);
        addSimpul(inputSimpul, &G);
        simpul *begin = findSimpul(inputSimpul, G);

        scanf(" %c", &inputSimpul.a);
        addSimpul(inputSimpul, &G);
        simpul *end = findSimpul(inputSimpul, G);

        scanf("%d", &inputJalur.b);
        addJalur(begin, end, inputJalur);
    }

    scanf(" %c", &inputSimpul.a);
    simpul *begin = findSimpul(inputSimpul, G);
    scanf(" %c", &inputSimpul.a);
    simpul *end = findSimpul(inputSimpul, G);

    // char path[n];
    dataPath curPath;
    dataPath *maxPath;
    (*maxPath).jarak = -1;
    findRoute(begin, end, curPath, maxPath, 0, 0);
    // yang terdekat
    printf("Yang terdekat:\n");
    for (int i = 0; i <= (*maxPath).path_index; i++)
                    printf("%c ", (*maxPath).path[i]);
                printf("%d\n", (*maxPath).jarak);

return 0;
}