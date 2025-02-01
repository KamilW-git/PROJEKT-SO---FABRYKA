#ifndef SEMAFOR_H
#define SEMAFOR_H

#include <sys/ipc.h>
#include <sys/sem.h>

extern int sem_id;

void inicjalizuj_semafor();
void wyczysc_semafor();
void czekaj_na_semaforze();
void sygnalizuj_semafor();

#endif