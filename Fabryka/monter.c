#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pamiec_dzielona.h"
#include "kolejka_komunikatow.h"
#include "semafor.h"

void proces_montera(int id) {
    while (1) {
        if (odbierz_wiadomosc() == 2 || odbierz_wiadomosc() == 3 || odbierz_wiadomosc() == 4) {
            printf("Monter %d: Kończę pracę.\n", id);
            break;
        }

        if (pamiec->magazyn_otwarty) {
            int podzespoly[3];
            if (pobierz_podzespoly_z_magazynu(podzespoly)) {
                printf("Monter %d: Wyprodukowano produkt!\n", id);
                sleep(2);
            } else {
                printf("Monter %d: Brak podzespołów!\n", id);
            }
        }

        sleep(1);
    }
    exit(0);
}