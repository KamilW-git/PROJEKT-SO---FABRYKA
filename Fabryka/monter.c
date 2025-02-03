#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pamiec_dzielona.h"
#include "kolejka_komunikatow.h"
#include "semafor.h"

void proces_montera(int id) {
    while (1) {
        // Sprawdź, czy jest polecenie zamknięcia (3 lub 4)
        int polecenie = odbierz_wiadomosc();
        if (polecenie == 3 || polecenie == 4) {
            printf("Monter %d: Kończę pracę.\n", id);
            break;
        }

        // Sprawdź, czy fabryka jest aktywna
        if (!pamiec->fabryka_aktywna) {
            printf("Monter %d: Fabryka zatrzymana, czekam...\n", id);
            sleep(2);
            continue;
        }

        // Sprawdź, czy magazyn jest otwarty
        if (pamiec->magazyn_otwarty) {
            // Sekcja krytyczna: dostęp do magazynu
            czekaj_na_semaforze(); // Zablokuj semafor
            if (pobierz_podzespoly_z_magazynu()) {
                printf("Monter %d: Pobrano podzespoły X, Y, Z\n", id);
                sygnalizuj_semafor(); // Odblokuj semafor

                // Symulacja przenoszenia i montowania
                printf("Monter %d: Przenoszę podzespoły na stanowisko %c...\n", id, 'A' + id);
                sleep(2);
                printf("Monter %d: Wyprodukowano produkt!\n", id);
            } else {
                sygnalizuj_semafor(); // Odblokuj semafor
                printf("Monter %d: Brak podzespołów w magazynie!\n", id);
            }
        }

        sleep(1);
    }
    exit(0);
}