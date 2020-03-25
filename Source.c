#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define N 16000000
#define BROJ -5


typedef struct OE_
{
    int x;
    struct OE_* sljedeci;
}OE;
//typedef struct OE_ OE;
OE* prvi = NULL;

time_t t1, t2;
int* V;

/*kod mene ne radi(dode do oko 4400 i crasha se), koristio sam ovo ispod*/
OE* gen_popisa(OE* prethodni, int i) {
	prethodni = (OE*)malloc(sizeof(OE_));
	prethodni->x = V[i];
	
	printf("\n%d", i);
	if (i < (N-1)) {
		OE* o = NULL;
		prethodni->sljedeci = gen_popisa(o, i+1);
		return prethodni;
	}
	else {
		prethodni->sljedeci = NULL;
	}
}

void generiranje(OE* prvi) {
	OE* prethodni = prvi;
	OE* trenutni = NULL;

	for (int i=0; i < (N-1); i++) {
		trenutni = (OE*)malloc(sizeof(OE_));
		trenutni->x = V[i];
		trenutni->sljedeci = NULL;
		prethodni->sljedeci = trenutni;
		prethodni = trenutni;
	}
}

void gen_arr() {
	srand(time(NULL));

	for (int i = 0; i < N; i++) {
		V[i] = rand() % 1000;
	}
}

int pret_popisa(OE* prvi, int broj) {
	OE_* trenutni = prvi;
	int i = 0;

	while (trenutni != NULL) {	
		if ((trenutni->x) == broj) {
			return i;
		}
		else {
			trenutni = trenutni->sljedeci;
		}
	i++;
	}
	return -1;
}

int pret_niz(int broj) {
	for (int i = 0; i < N; i++) {
		if (V[i] == broj) {
			return i;
		}
	}
	return -1;
}

void ispis_povezane(OE* prvi) {
	int x = prvi->x;
	printf("\n%d", x);
	if (prvi->sljedeci != NULL) {
		return ispis_povezane(prvi->sljedeci);
	}
}

int main()
{
    printf("--Algoritmi-LV2--\n");
	V =(int*) malloc(sizeof(int) * N);

	/*generiranje polja*/
	t1 = clock();
	gen_arr();
	t2 = clock();
	printf("\nVrijeme generiranja niza: %d ms", t2 - t1);

	/*pretvaranje polja u povezanu listu (popis)*/
	prvi = (OE*)malloc(sizeof(OE_));
	t1 = clock();
	//prvi = gen_popisa(prvi, 0);
	generiranje(prvi);
	t2 = clock();
	printf("\nVrijeme generiranja niza: %d ms", t2 - t1);

	//ispis_povezane(prvi);
	
	/*pretrazivanje niza*/
	t1 = clock();
	pret_niz(BROJ);
	t2 = clock();
	printf("\nVrijeme pretrazivanja niza: %d ms", t2 - t1);

	/*pretrazivanje povezane liste*/
	t1 = clock();
	pret_popisa(prvi, BROJ);
	t2 = clock();
	printf("\nVrijeme pretrazivanja popisa: %d ms", t2 - t1);

	return 0;
}
