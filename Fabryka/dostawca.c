#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pamiec_dzielona.h"
#include "kolejka_komunikatow.h"
#include "semafor.h"

void proces_dostawcy(int id) {
    while (1) {
        // Sprawdź, czy jest polecenie zamknięcia systemu (3 lub 4)
        int polecenie = odbierz_wiadomosc();
        if (polecenie == 3 || polecenie == 4) {
            printf("\033[1;34mDostawca %d\033[0m: \033[1;30mKończę pracę.\033[0m\n", id);
            break;
        }

        // Sprawdź, czy magazyn jest otwarty
        if (!pamiec->magazyn_otwarty) {
            printf("\033[1;34mDostawca %d\033[0m: \033[1;33mMagazyn zamknięty, czekamy na otwarcie...\033[0m\n", id);
            sleep(2);
            continue;
        }

        // Reszta logiki dostawcy
        int rozmiar = id + 1;
        if (sprawdz_miejsce_w_magazynie(rozmiar)) {
            dodaj_podzespol_do_magazynu(id, rozmiar);
            printf("\033[1;34mDostawca %d\033[0m: Dostarczono podzespół %c\n", id, 'X' + id);
        } else {
            printf("\033[1;34mDostawca %d\033[0m: \033[1;31mBrak miejsca!\033[0m\n", id);
        }

        sleep(1);
    }
    exit(0);
}