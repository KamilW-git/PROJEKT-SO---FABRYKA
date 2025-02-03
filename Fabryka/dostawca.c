#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pamiec_dzielona.h"
#include "kolejka_komunikatow.h"
#include "semafor.h"

void proces_dostawcy(int id) {
    while (1) {
        // Sprawdź, czy jest polecenie zamknięcia (3 lub 4)
        int polecenie = odbierz_wiadomosc();
        if (polecenie == 3 || polecenie == 4) {
            printf("Dostawca %d: Kończę pracę.\n", id);
            break;
        }

        // Sprawdź, czy fabryka jest aktywna
        if (!pamiec->fabryka_aktywna) {
            printf("Dostawca %d: Fabryka zatrzymana, czekam...\n", id);
            sleep(2);
            continue;
        }

        // Reszta logiki dostawcy
        if (pamiec->magazyn_otwarty) {
            int rozmiar = id + 1;
            if (sprawdz_miejsce_w_magazynie(rozmiar)) {
                dodaj_podzespol_do_magazynu(id, rozmiar);
                printf("Dostawca %d: Dostarczono podzespół %c\n", id, 'X' + id);
            } else {
                printf("Dostawca %d: Brak miejsca!\n", id);
            }
        }

        sleep(1);
    }
    exit(0);
}