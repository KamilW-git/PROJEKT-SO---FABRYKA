#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "pamiec_dzielona.h"
#include "kolejka_komunikatow.h"
#include "semafor.h"

void proces_dyrektora() {
    char input;
    while (1) {
        printf("\nDyrektor: wprowadź polecenie 1-4: ");
        if (scanf(" %c", &input) != 1) {
            while (getchar() != '\n'); // Czyszczenie błędnego wejścia
            continue;
        }
        while (getchar() != '\n'); // Czyszczenie bufora

        int polecenie = input - '0';

        switch (polecenie) {
            case 1:
                printf("[INFO] Zamykanie magazynu...\n");
            pamiec->magazyn_otwarty = 0; // Zamknij magazyn
            break;
            case 2:
                printf("[INFO] Zamykanie fabryki...\n");
            wyslij_wiadomosc(2); // Wyślij polecenie do wszystkich
            break;
            case 3:
                printf("[INFO] Zamykanie systemu (z zapisem stanu)...\n");
            zapisz_stan_magazynu();
            wyslij_wiadomosc(3);
            exit(0);
            case 4:
                printf("[INFO] Zamykanie systemu (bez zapisu)...\n");
            wyslij_wiadomosc(4);
            exit(0);
            default:
                printf("[BŁĄD] Nieprawidłowe polecenie!\n");
        }
    }
}