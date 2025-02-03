#ifndef KOLEJKA_KOMUNIKATOW_H
#define KOLEJKA_KOMUNIKATOW_H

#include <sys/ipc.h>
#include <sys/msg.h>
#include <stddef.h>

struct wiadomosc {
    long mtype;
    int polecenie;
};

extern int msg_id;

void inicjalizuj_kolejke_komunikatow();
void wyczysc_kolejke_komunikatow();
void wyczysc_kolejke();
void wyslij_wiadomosc(int polecenie);
int odbierz_wiadomosc();

#endif