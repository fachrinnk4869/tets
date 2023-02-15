#include "header.h"

void createEmpty(graph *G){
    (*G).first = NULL;
}

void addSimpul(dataSimpul inputSimpul, graph *G){

    simpul *baru;
    baru = (simpul *) malloc (sizeof(simpul));

    baru->kontainer = inputSimpul;
    baru->kontainer.visited = 0;
    baru->next = NULL;
    baru->first_jalur = NULL;

    if((*G).first == NULL){
        /*jika graf kosong*/
        (*G).first = baru;
    }
    else{
        
        /*menambahkan simpul baru pada akhir
        graph*/
        simpul *last = (*G).first;
        while(last->next != NULL){
            last = last->next;
        }

        last->next = baru;
    }
}

void addJalur(simpul *awal, simpul *tujuan, dataJalur beban){
    if((awal != NULL) && (tujuan != NULL)){
        jalur *baru;
        baru = (jalur *) malloc (sizeof (jalur));

        baru->kontainer_jalur = beban;
        baru->next_jalur = NULL;
        baru->tujuan = tujuan;

        if(awal->first_jalur == NULL){
            /*jika list jalur kosong*/
            awal->first_jalur = baru;
        }
        else{
            /*menambahkan jalur baru pada akhir list
            jalur*/
            jalur *last = awal->first_jalur;
            while(last->next_jalur != NULL){
                last = last->next_jalur;
            }
            last->next_jalur = baru;
        }
    }
}

simpul* findSimpul(dataSimpul inputSimpul, graph G){

    simpul *hasil = NULL;
    simpul *bantu = G.first;
    int ketemu = 0;

    while((bantu != NULL) && (ketemu == 0)){

        if(bantu->kontainer.a == inputSimpul.a){
            hasil = bantu;
            ketemu = 1;
        }
        else{
            bantu = bantu->next;
        }
    }
    return hasil;
}

elemen* findElemen(dataSimpul inputSimpul, list L){

    elemen *hasil = NULL;
    elemen *bantu = L.first;
    int ketemu = 0;

    while((bantu != NULL) && (ketemu == 0)){

        if(bantu->kontainer.a == inputSimpul.a){
            hasil = bantu;
            ketemu = 1;
        }
        else{
            bantu = bantu->next;
        }
    }
    return hasil;
}

void delJalur(dataSimpul ctujuan, simpul *awal){

    jalur *hapus = awal->first_jalur;
    
    if(hapus != NULL){

        jalur *prev = NULL;
        /*mencari jalur yang akan dihapus*/
        int ketemu = 0;
        while((hapus != NULL) && (ketemu == 0)){

            if(hapus->tujuan->kontainer.a == ctujuan.a){
                ketemu = 1;
            }
            else{
                prev = hapus;
                hapus = hapus->next_jalur;
            }
        }

        if(ketemu == 1){

            if(prev == NULL){
                /*hapus jalur pertama*/
                awal->first_jalur = hapus->next_jalur;
                hapus->next_jalur = NULL;
            }
            else{
                if(hapus->next_jalur == NULL){
                    /*hapus jalur terakhir*/
                    prev->next_jalur = NULL;
                }
                else{
                    /*hapus jalur di tengah*/
                    prev->next_jalur = hapus->next_jalur;
                    hapus->next_jalur = NULL;
                }
            }
            free(hapus);
        }
        else{
            // printf("tidak ada jalur dengan simpul tujuan\n");
        }
    }
    else{
        // printf("tidak ada jalur dengan simpul tujuan\n");
    }
}

void delAll(simpul *awal){

    jalur *bantu;
    bantu = awal->first_jalur;
    jalur *hapus;

    while(bantu != NULL){

        hapus = bantu;
        bantu = bantu->next_jalur;
        awal->first_jalur = bantu;
        hapus->next_jalur = NULL;
        free(hapus);
    }
}

void delSimpul(dataSimpul inputSimpul, graph *G){

    simpul *hapus = (*G).first;
    if(hapus != NULL){

        simpul *prev = NULL;
        /*mencari simpul yang akan dihapus*/
        int ketemu = 0;
        while((hapus != NULL) && (ketemu == 0)){
            if(hapus->kontainer.a == inputSimpul.a){
                ketemu = 1;
            }
            else{
                prev = hapus;
                hapus = hapus->next;
            }
        }

        if(ketemu == 1){
            /* jika simpul yang akan dihapus ada */
            /* hapus semua jalur dari simpul lain yang mengarah pada simpul yang dihapus */

            simpul *bantu;
            bantu = (*G).first;
            /* memeriksa semua simpul dalam graf */
            while(bantu != NULL){
                /* jika simpul yang ditelusuri tidak sama
                dengan yang dihapus */
                if(bantu != hapus){
                    /* hapus semua jalur yang mengarah pada
                    simpul yang dihapus */
                    delJalur(hapus->kontainer, bantu);
                }
                bantu = bantu->next;
            }

            /* hapus semua jalur */
            delAll(hapus);

            if(prev == NULL){
                /*hapus simpul pertama*/
                (*G).first = hapus->next;
                hapus->next = NULL;
            }
            else{
                if(hapus->next == NULL){
                    /*hapus simpul terakhir*/
                    prev->next = NULL;
                }
                else{
                    /*hapus simpul di tengah*/
                    prev->next = hapus->next;
                    hapus->next = NULL;
                }
            }
            free(hapus);
        }
        else{
            // printf("");
        }
    }
    else{
        // printf("");
    }
}

void printGraph(graph G){

    simpul *bantu = G.first;
    if(bantu != NULL){

        while(bantu != NULL){

            printf("Node %d\n", bantu->kontainer.a);
            jalur *bantu_jalur = bantu->first_jalur;

            while(bantu_jalur != NULL){
                printf("- Jalur %d ke %d\n", bantu->kontainer.a,
                bantu_jalur->tujuan->kontainer.a);
                bantu_jalur = bantu_jalur->next_jalur;
            }
            bantu = bantu->next;
        }
    }
    else{
        printf("graf kosong\n");
    }
}

void findRoute(simpul *awal, simpul *tujuan, dataPath curPath, dataPath *maxPath, int path_index, int jarak){
    simpul *bantu = awal;
    if(bantu != NULL){
        awal->kontainer.visited = 1;
        curPath.path[path_index] = awal->kontainer.a;

        if(awal == tujuan){
            for (int i = 0; i <= path_index; i++)
                printf("%c ", curPath.path[i]);
            curPath.jarak = jarak;
            curPath.path_index = path_index;
            printf("%d\n", curPath.jarak);
            if((*maxPath).jarak < curPath.jarak){
                (*maxPath) = curPath;
            }
        }else{

            jalur *bantu_jalur = bantu->first_jalur;

            while(bantu_jalur != NULL){
                if(bantu_jalur->tujuan->kontainer.visited == 0)
                    findRoute(bantu_jalur->tujuan, tujuan, curPath, maxPath, path_index + 1, jarak + bantu_jalur->kontainer_jalur.b);
                bantu_jalur = bantu_jalur->next_jalur;
            }
        }
        awal->kontainer.visited = 0;
    }
}