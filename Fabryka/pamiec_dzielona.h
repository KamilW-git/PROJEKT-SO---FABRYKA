#ifndef PAMIEC_DZIELONA_H
#define PAMIEC_DZIELONA_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define MAX_JEDNOSTEK 100

struct pamiec_dzielona {
    int jednostki_magazynowe;
    int magazyn_otwarty;
};

// Deklaracja zmiennej globalnej
extern int shm_id;
extern struct pamiec_dzielona *pamiec;

void inicjalizuj_pamiec_dzielona();
void wyczysc_pamiec_dzielona();
int sprawdz_miejsce_w_magazynie(int rozmiar);
void dodaj_podzespol_do_magazynu(int typ, int rozmiar);
int pobierz_podzespoly_z_magazynu(int podzespoly[3]);
void zapisz_stan_magazynu();

#endif