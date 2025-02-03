#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pamiec_dzielona.h"
#include "kolejka_komunikatow.h"
#include "semafor.h"

void proces_dyrektora() {
    char input;
    while (1) {
        printf("\nDyrektor: wprowadź polecenie (1-6): ");
        if (scanf(" %c", &input) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        int polecenie = input - '0';

        switch (polecenie) {
            case 1:
                printf("[INFO] Zamykanie magazynu...\n");
            pamiec->magazyn_otwarty = 0;
            break;
            case 2:
                printf("[INFO] Zamykanie fabryki...\n");
            pamiec->fabryka_aktywna = 0;
            break;
            case 3:
                printf("[INFO] Zamykanie systemu (z zapisem stanu)...\n");
            zapisz_stan_magazynu();
            // Wyślij 5 komunikatów (3 dostawców + 2 monterów)
            for (int i = 0; i < 5; i++) wyslij_wiadomosc(3);
            exit(0);
            case 4:
                printf("[INFO] Zamykanie systemu (bez zapisu)...\n");
            // Wyślij 5 komunikatów (3 dostawców + 2 monterów)
            for (int i = 0; i < 5; i++) wyslij_wiadomosc(4);
            exit(0);
            case 5:
                printf("[INFO] Wznawianie pracy magazynu...\n");
            pamiec->magazyn_otwarty = 1;
            break;
            case 6:
                printf("[INFO] Wznawianie pracy fabryki...\n");
            pamiec->fabryka_aktywna = 1;
            break;
            default:
                printf("[BŁĄD] Nieprawidłowe polecenie!\n");
        }
    }
}