#include "pamiec_dzielona.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>

int shm_id;
struct pamiec_dzielona *pamiec;
int sem_id;

void inicjalizuj_pamiec_dzielona() {
    shm_id = shmget(IPC_PRIVATE, sizeof(struct pamiec_dzielona), 0666);
    pamiec = (struct pamiec_dzielona *)shmat(shm_id, NULL, 0);
    pamiec->jednostki_magazynowe = 0;
    pamiec->magazyn_otwarty = 1;
    pamiec->fabryka_aktywna = 1;
    pamiec->podzespoly[0] = 0; // X
    pamiec->podzespoly[1] = 0; // Y
    pamiec->podzespoly[2] = 0; // Z

    // Inicjalizacja semafora
    sem_id = semget(IPC_PRIVATE, 1, 0666);
    semctl(sem_id, 0, SETVAL, 1); // Ustaw wartość początkową na 1

    // Wczytaj stan magazynu z pliku (jeśli istnieje)
    wczytaj_stan_magazynu();
}

void wyczysc_pamiec_dzielona() {
    shmdt(pamiec);
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);
}

int sprawdz_miejsce_w_magazynie(int rozmiar) {
    return (pamiec->jednostki_magazynowe + rozmiar <= MAX_JEDNOSTEK);
}

void dodaj_podzespol_do_magazynu(int typ, int rozmiar) {
    pamiec->jednostki_magazynowe += rozmiar;
    pamiec->podzespoly[typ]++; // Zwiększ liczbę podzespołów danego typu
}

int pobierz_podzespoly_z_magazynu() {
    // Sprawdź, czy są dostępne wszystkie podzespoły
    if (pamiec->podzespoly[0] >= 1 && pamiec->podzespoly[1] >= 1 && pamiec->podzespoly[2] >= 1) {
        pamiec->podzespoly[0]--; // X
        pamiec->podzespoly[1]--; // Y
        pamiec->podzespoly[2]--; // Z
        pamiec->jednostki_magazynowe -= 6; // 1 + 2 + 3 = 6 jednostek
        return 1; // Sukces
    }
    return 0; // Brak podzespołów
}

void zapisz_stan_magazynu() {
    FILE *plik = fopen("stan_magazynu.txt", "w");
    if (plik == NULL) {
        perror("Błąd podczas otwierania pliku");
        return;
    }
    fprintf(plik, "Jednostki magazynowe: %d\n", pamiec->jednostki_magazynowe);
    fprintf(plik, "Podzespoły: X=%d, Y=%d, Z=%d\n", pamiec->podzespoly[0], pamiec->podzespoly[1], pamiec->podzespoly[2]);
    fclose(plik);
}

void wczytaj_stan_magazynu() {
    FILE *plik = fopen("stan_magazynu.txt", "r");
    if (plik == NULL) {
        printf("[INFO] Brak pliku stanu magazynu. Używam stanu domyślnego.\n");
        return;
    }

    // Wczytaj dane z pliku
    int wczytane = fscanf(plik, "Jednostki magazynowe: %d\nPodzespoły: X=%d, Y=%d, Z=%d\n",
                          &pamiec->jednostki_magazynowe,
                          &pamiec->podzespoly[0],
                          &pamiec->podzespoly[1],
                          &pamiec->podzespoly[2]);

    if (wczytane != 4) {
        printf("[BŁĄD] Nie udałSo się wczytać pełnego stanu magazynu z pliku.\n");
        // Przywróć stan domyślny
        pamiec->jednostki_magazynowe = 0;
        pamiec->podzespoly[0] = 0;
        pamiec->podzespoly[1] = 0;
        pamiec->podzespoly[2] = 0;
    } else {
        printf("[INFO] Wczytano stan magazynu z pliku:\n");
        printf("  Jednostki magazynowe: %d\n", pamiec->jednostki_magazynowe);
        printf("  Podzespoły: X=%d, Y=%d, Z=%d\n", pamiec->podzespoly[0], pamiec->podzespoly[1], pamiec->podzespoly[2]);
    }

    fclose(plik);
}