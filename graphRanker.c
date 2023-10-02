#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MASSIMO INT_MAX
#define BUFFER 3000

//STRUTTURE AGGREGATE

typedef struct {
long int numero_grafo;
long int  peso_grafo;

}grafo;

typedef enum {F,T} mybool;

typedef struct{
mybool processato;
long int sdist;
long int numero_nodo;
}nodo;

//FUNZIONI
void AggiungiGrafo(char *lettura_riga,long int nodi, long int **matrice_pesi,nodo *tabella,long int *lunghezza_heap,long int k, grafo*classifica);
//FUNZIONI PER IL CALCOLO DEI PESI DEI GRAFI
long int trovo_nodo_corrente(nodo vettore[],long int nodi);
mybool nodi_processati(nodo vettore[],long int nodi);
long int somma_peso_grafo(nodo vettore[],long int  nodi);
long int peso_percorso_minimo(long int  **matrice_pesi,nodo*tabella,long int nodi);
//FUNZIONI PER RIODINARE LA CLASSIFICA
void build_max_heap(grafo* classifica,long int lunghezza_heap);
void max_heapify(grafo*classifica,long int z,long int numeri_grafi);


int main()
{
    //DICHIARAZIONE VARIABILI USATE  E ASSEGNAMENTO VALORI ALLE VARIABILI
    long int nodi;
    long int k  ;
    long int lunghezza_heap = 0;
    long int numero_cifre = 7;
    char *lettura_riga;
    //char stringa_temporanea[10];
    /*
    if(fgets(stringa_temporanea,10,stdin)!=NULL)
    {
        nodi = strtol(stringa_temporanea,&lettura_riga,10);
        lettura_riga++;
        k = strtol(lettura_riga,&lettura_riga,10);
    }
    */
    if(scanf("%ld %ld",&nodi,&k)!=2)
    {
        printf("error");
    }
    //INIZIALIZZAZIONE DELLE STRUTTURE NECESSARIE
    lettura_riga = (char*)malloc(sizeof(char)*(nodi*numero_cifre));
    grafo *classifica = malloc(k*sizeof(grafo));
    nodo *tabella = malloc(nodi*(sizeof(nodo)));
    long int**pesi = malloc(nodi*sizeof(long int *));
    for(int i=0;i<nodi;i++)
    {
        pesi[i] = malloc(nodi*sizeof(long int ));
    }
    while(fgets(lettura_riga,BUFFER,stdin)!=NULL)
    {
        if(lettura_riga[0]=='A')
        {
            AggiungiGrafo(lettura_riga,nodi,pesi,tabella,&lunghezza_heap,k,classifica);

        }else if(lettura_riga[0]=='T')
        {
            if(lunghezza_heap<k)
            {
                for(int i=0;i<lunghezza_heap;i++)
                {
                    if(i==lunghezza_heap-1)
                    {
                        printf("%ld",classifica[i].numero_grafo);
                    }else{
                        printf("%ld ",classifica[i].numero_grafo);
                    }
                }
            }else if(lunghezza_heap>=k)
            {
                for(int i=0;i<k;i++)
                {
                    if(i==k-1)
                    {
                        printf("%ld",classifica[i].numero_grafo);
                    }else{
                        printf("%ld ",classifica[i].numero_grafo);
                    }
                }
            }
            printf("\n");
        }
    }
    //ANDIAMO A CHIUDERE IL FILE E A DEALLOCARE SPAZIO
    for(int i=0;i<nodi;i++)
    {
        free(pesi[i]);
    }
    free(pesi);
    free(lettura_riga);
    free(tabella);
    free(classifica);

  return 0;
}

void AggiungiGrafo(char *lettura_riga,long int nodi, long int **matrice_pesi,nodo *tabella,long int  *lunghezza_heap,long int  k, grafo*classifica)
{
    //DICHIARAZIONE DELLE VARIABILI
    char*delimitatore;
    long int  peso;
    //INSERIMENTO DATI IN MATRICE
    for(int i=0;i<nodi;i++)
    {
        if(fgets(lettura_riga,BUFFER,stdin)!=NULL)
        {
            matrice_pesi[i][0] = strtol(lettura_riga,&delimitatore,10);
            delimitatore++;
            for(int j=1;j<nodi;j++)
            {
                matrice_pesi[i][j] = strtol(delimitatore,&delimitatore,10);
                delimitatore++;

            }
        }
    }
    //CALCOLO DEL PESO DEL PERCORSO A PESO MINIMO
    peso = peso_percorso_minimo(matrice_pesi,tabella,nodi);
    //INSERIMENTO IN CLASSIFICA DEI GRAFI CON I RELATIVI PESI
    if(*lunghezza_heap<k)
    {
        classifica[*lunghezza_heap].numero_grafo = *lunghezza_heap;
        classifica[*lunghezza_heap].peso_grafo = peso;
    }else if(*lunghezza_heap==k)
    {
        build_max_heap(classifica,k);
        if(peso<classifica[0].peso_grafo)
        {
            classifica[0].numero_grafo = *lunghezza_heap;
            classifica[0].peso_grafo = peso;
            max_heapify(classifica,0,k);
        }
    }else if(*lunghezza_heap>k && classifica[0].peso_grafo>peso)
    {
        classifica[0].numero_grafo = *lunghezza_heap;
        classifica[0].peso_grafo = peso;
        max_heapify(classifica,0,k);
    }
    *lunghezza_heap = *lunghezza_heap+1;

}


long int peso_percorso_minimo(long int **matrice_pesi,nodo*tabella,long int nodi)
{
  //DICHIARAZIONE DELLE VARIABILI
  long int  nodo_corrente,peso_grafo;
  //ASSEGNAMENTI
  for(int i=0;i<nodi;i++)
  {
      tabella[i].processato = F;
      tabella[i].numero_nodo = i;
      if(i==0)
      {
          tabella[i].sdist = 0;
      }else{
          tabella[i].sdist = MASSIMO;
      }
  }
  //CALCOLO DEL PERCORSO PESI MINIMO
  nodo_corrente = 0;
  do{
     for(int i=1;i<nodi;i++)
     {
         if((nodo_corrente!=i) && matrice_pesi[nodo_corrente][i]!=0 && (matrice_pesi[nodo_corrente][i]+tabella[nodo_corrente].sdist<tabella[i].sdist))
         {
             tabella[i].sdist = matrice_pesi[nodo_corrente][i]+tabella[nodo_corrente].sdist;
         }
    }
     tabella[nodo_corrente].processato = T;
     nodo_corrente = trovo_nodo_corrente(tabella,nodi);
  }while((tabella[nodo_corrente].sdist!= MASSIMO) && (nodi_processati(tabella,nodi)!=T));
  peso_grafo = somma_peso_grafo(tabella,nodi);
  return peso_grafo;
}

long int trovo_nodo_corrente(nodo vettore[],long int nodi)
{
    //DICHIARAZIONE VARIABILI
    long int minimo,nodo_corrente,i;
    //ASSEGNAMENTI
    minimo = MASSIMO;
    nodo_corrente = 0;
    //CALCOLO NODO CORRENTE
    for(i=1;i<nodi;i++)
    {
        if(vettore[i].processato!=T && vettore[i].sdist <= minimo)
        {
            minimo = vettore[i].sdist;
            nodo_corrente = i;
        }
    }
    return nodo_corrente;

}
mybool nodi_processati(nodo vettore[],long int  nodi)
{
    //DICHIARAZIONE VARIABILI
    mybool processati = T;
    int i;
    //ASSEGNAMENTI
    i = 0;
    //CONTROLLO NODI PROCESSATI
    do{
        if(vettore[i].processato!=T)
        {
            processati = F;
        }
        i++;
    }while(processati == T && i<nodi);
    return processati;
}
long int  somma_peso_grafo(nodo vettore[],long int nodi)
{
    //DICHIARAZIONE VARIABILI
    long int peso_grafo ,peso_nodo;
    //ASSEGNAMENTI
    peso_grafo = 0 ;
    //CALCOLO DEL PESO DI UN GRAFO
    for(int i = 1; i<nodi;i++)
    {
        if(vettore[i].sdist == MASSIMO)
        {
            peso_nodo = 0;
        }else{
            peso_nodo = vettore[i].sdist;
        }
        peso_grafo = peso_grafo + peso_nodo;
    }
    return peso_grafo;
}

void build_max_heap(grafo* classifica,long int  lunghezza_heap)
{
    //DICHIARAZIONE E ASSEGNAMENTI A VARIABILI
    long int half = lunghezza_heap/2;
    //COSTRUZIONE DEL MAX_HEAP
    for (int i = half;i>=0;i--)
    {
        max_heapify(classifica,i,lunghezza_heap);
    }
}

void max_heapify(grafo*classifica,long int z,long int  numeri_grafi)
{
    //DICHIARAZIONE E ASSEGNAMENTO VARIABILI
    long int figlio_sinistro = 2*z+1;
    long int figlio_destro = 2*z+2;
    long int max;
    long int temp;

    //CALCOLO MAX_HEAPIFY
     if(figlio_sinistro < numeri_grafi && classifica[figlio_sinistro].peso_grafo > classifica[z].peso_grafo)
    {
        max = figlio_sinistro;

    }else{

        max = z;

    }

    if(figlio_destro < numeri_grafi && classifica[figlio_destro].peso_grafo> classifica[max].peso_grafo)
    {
        max = figlio_destro;

    }

    if(max!=z)
    {
        //SCAMBIO:
        temp = classifica[z].peso_grafo;
        classifica[z].peso_grafo = classifica[max].peso_grafo;
        classifica[max].peso_grafo = temp;

        temp = classifica[z].numero_grafo;
        classifica[z].numero_grafo = classifica[max].numero_grafo;
        classifica[max].numero_grafo = temp;
        max_heapify(classifica,max,numeri_grafi);
    }

}























