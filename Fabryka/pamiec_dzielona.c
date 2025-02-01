#include <stdio.h>
#include "pamiec_dzielona.h"
#include <sys/ipc.h>
#include <sys/shm.h>

// Zmienna globalna przechowująca identyfikator segmentu pamięci dzielonej
int shm_id;

// Wskaźnik do pamięci dzielonej
struct pamiec_dzielona *pamiec;

void inicjalizuj_pamiec_dzielona() {
    // Tworzenie segmentu pamięci dzielonej
    shm_id = shmget(IPC_PRIVATE, sizeof(struct pamiec_dzielona), 0666);
    if (shm_id == -1) {
        perror("Błąd podczas tworzenia pamięci dzielonej");
        exit(EXIT_FAILURE);
    }

    // Przypisanie wskaźnika do pamięci dzielonej
    pamiec = (struct pamiec_dzielona *)shmat(shm_id, NULL, 0);
    if (pamiec == (void *)-1) {
        perror("Błąd podczas przypisywania pamięci dzielonej");
        exit(EXIT_FAILURE);
    }

    // Inicjalizacja danych w pamięci dzielonej
    pamiec->jednostki_magazynowe = 0;
    pamiec->magazyn_otwarty = 1; // Magazyn początkowo otwarty
}

void wyczysc_pamiec_dzielona() {
    // Odłączenie pamięci dzielonej
    if (shmdt(pamiec) == -1) {
        perror("Błąd podczas odłączania pamięci dzielonej");
    }

    // Usunięcie segmentu pamięci dzielonej
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("Błąd podczas usuwania pamięci dzielonej");
    }
}

int sprawdz_miejsce_w_magazynie(int rozmiar) {
    return (pamiec->jednostki_magazynowe + rozmiar <= MAX_JEDNOSTEK);
}

void dodaj_podzespol_do_magazynu(int typ, int rozmiar) {
    pamiec->jednostki_magazynowe += rozmiar;
}

int pobierz_podzespoly_z_magazynu(int podzespoly[3]) {
    if (pamiec->jednostki_magazynowe >= 6) {
        pamiec->jednostki_magazynowe -= 6;
        return 1;
    }
    return 0;
}

void zapisz_stan_magazynu() {
    FILE *plik = fopen("stan_magazynu.txt", "w");
    if (plik == NULL) {
        perror("Błąd podczas otwierania pliku");
        return;
    }
    fprintf(plik, "%d", pamiec->jednostki_magazynowe);
    fclose(plik);
}