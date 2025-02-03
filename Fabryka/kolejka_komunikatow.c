#include "kolejka_komunikatow.h"
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>

int msg_id;

void inicjalizuj_kolejke_komunikatow() {
    msg_id = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
    if (msg_id == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
}

void wyczysc_kolejke_komunikatow() {
    if (msgctl(msg_id, IPC_RMID, NULL) == -1) {
        perror("msgctl");
    }
}

void wyczysc_kolejke() {
    struct wiadomosc msg;
    // Pobierz wszystkie wiadomości z kolejki (aż do pustki)
    while (msgrcv(msg_id, &msg, sizeof(msg.polecenie), 1, IPC_NOWAIT) != -1) {
        printf("[DEBUG] Usunięto wiadomość: %d\n", msg.polecenie);
    }
}

void wyslij_wiadomosc(int polecenie) {
    struct wiadomosc msg;
    msg.mtype = 1; // Wszystkie komunikaty mają ten sam typ
    msg.polecenie = polecenie;
    if (msgsnd(msg_id, &msg, sizeof(msg.polecenie), 0) == -1) {
        perror("msgsnd");
    }
}

int odbierz_wiadomosc() {
    struct wiadomosc msg;
    if (msgrcv(msg_id, &msg, sizeof(msg.polecenie), 1, IPC_NOWAIT) == -1) {
        return -1; // Brak wiadomości
    }
    return msg.polecenie;
}