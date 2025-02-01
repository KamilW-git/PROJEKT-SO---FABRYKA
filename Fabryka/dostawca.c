#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pamiec_dzielona.h"
#include "kolejka_komunikatow.h"
#include "semafor.h"

void proces_dostawcy(int id) {
    while (1) {
        // Sprawdź, czy nie ma polecenia zamknięcia
        if (odbierz_wiadomosc() == 2 || odbierz_wiadomosc() == 3 || odbierz_wiadomosc() == 4) {
            printf("Dostawca %d: Kończę pracę.\n", id);
            break;
        }

        if (pamiec->magazyn_otwarty) { // Działaj tylko jeśli magazyn otwarty
            int rozmiar = id + 1;
            if (sprawdz_miejsce_w_magazynie(rozmiar)) {
                dodaj_podzespol_do_magazynu(id, rozmiar);
                printf("Dostawca %d: Dostarczono podzespół %c\n", id, 'X' + id);
            } else {
                printf("Dostawca %d: Brak miejsca!\n", id);
            }
        }

        sleep(1); // Symuluj czas dostawy
    }
    exit(0);
}