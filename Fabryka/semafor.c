#include "semafor.h"
#include <sys/ipc.h>
#include <sys/sem.h>

int sem_id;

void inicjalizuj_semafor() {
    sem_id = semget(IPC_PRIVATE, 1, 0666);
    semctl(sem_id, 0, SETVAL, 1);
}

void wyczysc_semafor() {
    semctl(sem_id, 0, IPC_RMID);
}

void czekaj_na_semaforze() {
    struct sembuf sb = {0, -1, 0};
    semop(sem_id, &sb, 1);
}

void sygnalizuj_semafor() {
    struct sembuf sb = {0, 1, 0};
    semop(sem_id, &sb, 1);
}