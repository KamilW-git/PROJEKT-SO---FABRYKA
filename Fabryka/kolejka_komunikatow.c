#include <stddef.h>
#include "kolejka_komunikatow.h"
#include <sys/ipc.h>
#include <sys/msg.h>

int msg_id;

void inicjalizuj_kolejke_komunikatow() {
    msg_id = msgget(IPC_PRIVATE, 0666);
}

void wyczysc_kolejke_komunikatow() {
    msgctl(msg_id, IPC_RMID, NULL);
}

void wyslij_wiadomosc(int polecenie) {
    struct wiadomosc msg;
    msg.mtype = 1;
    msg.polecenie = polecenie;
    msgsnd(msg_id, &msg, sizeof(msg), 0);
}

int odbierz_wiadomosc() {
    struct wiadomosc msg;
    msgrcv(msg_id, &msg, sizeof(msg), 1, IPC_NOWAIT);
    return msg.polecenie;
}