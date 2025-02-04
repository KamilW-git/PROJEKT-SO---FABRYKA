#ifndef PAMIEC_DZIELONA_H
#define PAMIEC_DZIELONA_H

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define MAX_JEDNOSTEK 100

struct pamiec_dzielona {
    int jednostki_magazynowe; // Liczba zajętych jednostek
    int magazyn_otwarty;      // 1 = otwarty, 0 = zamknięty
    int fabryka_aktywna;      // 1 = działa, 0 = zatrzymana
    int podzespoly[3];        // Liczba dostępnych podzespołów: X, Y, Z
};

extern int shm_id;
extern struct pamiec_dzielona *pamiec;

// Semafor do synchronizacji dostępu do magazynu
extern int sem_id;

void inicjalizuj_pamiec_dzielona();
void wyczysc_pamiec_dzielona();
int sprawdz_miejsce_w_magazynie(int rozmiar);
void dodaj_podzespol_do_magazynu(int typ, int rozmiar);
int pobierz_podzespoly_z_magazynu();
void zapisz_stan_magazynu();
void wczytaj_stan_magazynu();

#endif