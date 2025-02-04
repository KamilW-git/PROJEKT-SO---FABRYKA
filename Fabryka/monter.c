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
            printf("\033[1;35mMonter %d\033[0m: \033[1;30mKończę pracę.\033[0m\n", id);
            break;
        }

        // Sprawdź, czy fabryka jest aktywna
        if (!pamiec->fabryka_aktywna) {
            printf("\033[1;35mMonter %d\033[0m: Fabryka zatrzymana, czekam...\n", id);
            sleep(2);
            continue;
        }

        if (!pamiec->magazyn_otwarty) {
            printf("\033[1;35mMonter %d\033[0m: Magazyn zamknięty, nie mam jak pobrać podzespołów...\n", id);
            sleep(2);
            continue;
        }

        // Sprawdź, czy magazyn jest otwarty
        if (pamiec->magazyn_otwarty) {
            // Sekcja krytyczna: dostęp do magazynu
            czekaj_na_semaforze(); // Zablokuj semafor
            if (pobierz_podzespoly_z_magazynu()) {
                printf("\033[1;35mMonter %d\033[0m: Pobrano podzespoły X, Y, Z\n", id);
                sygnalizuj_semafor(); // Odblokuj semafor

                // Symulacja przenoszenia i montowania
                printf("\033[1;35mMonter %d\033[0m: Przenoszę podzespoły na stanowisko %c...\n", id, 'A' + id);
                sleep(2);
                printf("\033[1;35mMonter %d\033[0m: \033[1;32mWyprodukowano produkt!\033[0m\n", id);
            } else {
                sygnalizuj_semafor(); // Odblokuj semafor
                printf("\033[1;35mMonter %d\033[0m: \033[1;31mBrak podzespołów w magazynie!\033[0m\n", id);
            }
        }

        sleep(1);
    }
    exit(0);
}