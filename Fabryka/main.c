#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "pamiec_dzielona.h"
#include "kolejka_komunikatow.h"
#include "semafor.h"
#include "dyrektor.h"
#include "dostawca.h"
#include "monter.h"

int main() {
    inicjalizuj_pamiec_dzielona();
    inicjalizuj_kolejke_komunikatow();
    inicjalizuj_semafor();

    // Uruchom procesy dostawców
    for (int i = 0; i < 3; i++) {
        if (fork() == 0) {
            proces_dostawcy(i);
            exit(0);
        }
    }

    // Uruchom procesy monterów
    for (int i = 0; i < 2; i++) {
        if (fork() == 0) {
            proces_montera(i);
            exit(0);
        }
    }

    // Uruchom proces dyrektora
    proces_dyrektora();
    printf("[DEBUG] Wysyłam sygnał SIGTERM do wszystkich procesów...\n");
    kill(0, SIGTERM); // Zabija wszystkie procesy potomne

    // Czekaj na zakończenie procesów potomnych
    while (wait(NULL) > 0);

    wyczysc_pamiec_dzielona();
    wyczysc_kolejke_komunikatow();
    wyczysc_semafor();

    return 0;
}