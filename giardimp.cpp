#include <stdio.h>
#include <assert.h>

#define MAXN    500
#define MAXM    20
#define MAXINT  32767

int giardino_imperiale(int N, int M, int Stemma[MAXM][2], int Parco[MAXN][MAXN]) {
    int r[3];
    r[2]=MAXINT;                            //risultato il numero minimo di prato tagliato
    signed char dim_stemma[2];              //Le dimensioni dello stemma [x, y]
    signed char inizio_stemma[2];           //Inizio dello stemma [x, y]
    for(signed char i=0;i<1;i++){           //Per ridurre lo spazio
        signed char stemma_min_max[2][2];   //[min, max][x, y]
        stemma_min_max[0][0]=50;            //Settaggio min
        stemma_min_max[0][1]=50;
        for(signed char j=0;j<M;j++){
            if(stemma_min_max[0][0]>Stemma[0][j])
                stemma_min_max[0][0]=Stemma[0][j];
            if(stemma_min_max[0][1]>Stemma[1][j])
                stemma_min_max[0][1]=Stemma[1][j];

            if(stemma_min_max[1][0]<Stemma[0][j])
                stemma_min_max[1][0]=Stemma[0][j];
            if(stemma_min_max[1][1]<Stemma[1][j])
                stemma_min_max[1][1]=Stemma[1][j];
        }
        inizio_stemma[0]= stemma_min_max[0][0];                     //x, y d'inizio dello stemma
        inizio_stemma[1]= stemma_min_max[0][1];
        dim_stemma[0]= stemma_min_max[1][0]-stemma_min_max[0][0];   //x, y stemma
        dim_stemma[1]= stemma_min_max[1][1]-stemma_min_max[0][1];
    }
    for(signed char x=1;x<(N-dim_stemma[0]);x++){//ciclo fondamentale: calcolo di tutte le possibilità
        for(signed char y=1;y<(N-dim_stemma[1]);y++){
            int somma=0;
            for(signed char i=0;i<M;i++){
                somma+= Parco[Stemma[0][i]-inizio_stemma[0]+x][Stemma[1][i]-inizio_stemma[1]+y];
            }
            if(somma<r){
                r[0]= x-inizio_stemma[0];
                r[1]= y-inizio_stemma[2];
                r[2]= somma
            }
        }
    }

    return r;
}


int main() {
    FILE *fr, *fw;
    int N, M;
    int STC[20][2];
    int G[500][500];

    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");
    assert(2 == fscanf(fr, "%d%d", &N, &M));

    for(int i=0; i<M; i++)
        assert(2 == fscanf(fr, "%d%d", &STC[i][0],&STC[i][1]));

    for(int r=0; r<N; r++){
        for (int c=0;c<N;c++){
            assert(1 == fscanf(fr, "%d", &G[r][c]));
        }
    }

    double long R[3]=giardino_imperiale(N,M,STC,G);//"Trasferimento" dati
    for(int i=0;i<3;i++){
        fprintf(fw, "%.8f\n", R[i]);
    }
    fclose(fr);
    fclose(fw);
    return 0;
}
