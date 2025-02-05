//Raport i testy projektu „Fabryka”
//Raport 
 
//1.	Założenia projektowe 
//Program symuluje pracę fabryki z dwoma stanowiskami produkcyjnymi (A i B), magazynem o pojemności M oraz procesami: 
//•	Dostawcy: Dostarczają podzespoły X, Y, Z (1, 2, 3 jednostek magazynowych, w programie to jest rozwiązane tak, że Dostawcy mają ID numerowane od 0, a wielkość jednostki podzespołu jest określona jako ID dostawcy +1). 
//Funkcja realizująca procesy dostawców: 

void proces_dostawcy(int id) {
    while (1) {
        // Sprawdź, czy jest polecenie zamknięcia systemu (3 lub 4)
        int polecenie = odbierz_wiadomosc();
        if (polecenie == 3 || polecenie == 4) {
            printf("\033[1;34mDostawca %d\033[0m: \033[1;30mKończę pracę.\033[0m\n", id);
            break;
        }

        // Sprawdź, czy magazyn jest otwarty
        if (!pamiec->magazyn_otwarty) {
            printf("\033[1;34mDostawca %d\033[0m: \033[1;33mMagazyn zamknięty, czekamy na otwarcie...\033[0m\n", id);
            sleep(2);
            continue;
        }

        // Reszta logiki dostawcy
        int rozmiar = id + 1;
        if (sprawdz_miejsce_w_magazynie(rozmiar)) {
            dodaj_podzespol_do_magazynu(id, rozmiar);
            printf("\033[1;34mDostawca %d\033[0m: Dostarczono podzespół %c\n", id, 'X' + id);
        } else {
            printf("\033[1;34mDostawca %d\033[0m: \033[1;31mBrak miejsca!\033[0m\n", id);
        }

        sleep(1);
    }
    exit(0);
}


//•	Monterzy: Pobierają podzespoły z magazynu, przenoszą na swoje stanowisko (A lub B) i montują produkty. 
//Funkcja realizująca procesy monterów:

void proces_montera(int id) {

    int licznik=0;
    while (1) {
        // Sprawdź, czy jest polecenie zamknięcia (3 lub 4)
        int polecenie = odbierz_wiadomosc();
        if (polecenie == 3 || polecenie == 4) {
            printf("\033[1;35mMonter %d\033[0m: \033[1;30mKończę pracę.\033[0m\n", id);
            break;
        }

        // Sprawdź, czy fabryka jest aktywna
        if (!pamiec->fabryka_aktywna) {
            printf("\033[1;35mMonter %d\033[0m: Fabryka zatrzymana, czekam...\n", id);
            sleep(2);
            continue;
        }

        if (!pamiec->magazyn_otwarty) {
            printf("\033[1;35mMonter %d\033[0m: Magazyn zamknięty, nie mam jak pobrać podzespołów...\n", id);
            sleep(2);
            continue;
        }

        // Sprawdź, czy magazyn jest otwarty
        if (pamiec->magazyn_otwarty) {
            // Sekcja krytyczna: dostęp do magazynu
            czekaj_na_semaforze(); // Zablokuj semafor
            if (pobierz_podzespoly_z_magazynu()) {
                printf("\033[1;35mMonter %d\033[0m: Pobrano podzespoły X, Y, Z\n", id);
                sygnalizuj_semafor(); // Odblokuj semafor

                // Symulacja przenoszenia i montowania
                printf("\033[1;35mMonter %d\033[0m: Przenoszę podzespoły na stanowisko %c...\n", id, 'A' + id);
                sleep(2);
                licznik++;
                printf("\033[1;35mMonter %d\033[0m: \033[1;32mWyprodukowano produkt! = %d\033[0m\n", id, licznik);


            } else {
                sygnalizuj_semafor(); // Odblokuj semafor
                printf("\033[1;35mMonter %d\033[0m: \033[1;31mBrak podzespołów w magazynie!\033[0m\n", id);
            }
        }

        sleep(1);
    }
    exit(0);
}

//•	Dyrektor: Wydaje polecenia (1-6) zarządzające pracą fabryki i magazynu. 
//Funkcja realizująca obsługę poleceń Dyrektora: 

void proces_dyrektora() {
    char input;
    while (1) {
        printf("\nDyrektor: wprowadź polecenie (1-6): \n");
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
                printf("\033[1;31m[BŁĄD] Nieprawidłowe polecenie!\033[0m\n");
        }
    }
}

//•	Wymagania techniczne: Synchronizacja procesów, obsługa błędów (perror), minimalne prawa dostępu do struktur, usuwanie zasobów po zakończeniu. 
//2.	Ogólny opis kodu 
//•	Struktura projektu: 
//o	Procesy: dyrektor, dostawca, monter. o 	Komunikacja: Kolejka komunikatów do przesyłania poleceń. o 	Synchronizacja: Semafor binarny do ochrony dostępu do magazynu. 
//o	Pamięć dzielona: Przechowuje stan magazynu (jednostki_magazynowe, podzespoly). 


/*
Struktura plików projektu:

/fabryka/
│
├── main.c
├── dyrektor.c
├── dostawca.c
├── monter.c
├── pamiec_dzielona.c
├── kolejka_komunikatow.c
├── semafor.c
│
├── dyrektor.h
├── dostawca.h
├── monter.h
├── pamiec_dzielona.h
├── kolejka_komunikatow.h
├── semafor.h
 
 */

//•	Funkcje kluczowe: 
//void	zapisz_stan_magazynu(): Zapis stanu do pliku po poleceniu 3. 

void zapisz_stan_magazynu() {
    FILE *plik = fopen("stan_magazynu.txt", "w");
    if (plik == NULL) {
        perror("Błąd podczas otwierania pliku");
        return;
    }
    fprintf(plik, "Jednostki magazynowe: %d\n", pamiec->jednostki_magazynowe);
    fprintf(plik, "Podzespoły: X=%d, Y=%d, Z=%d\n", pamiec->podzespoly[0], pamiec->podzespoly[1], pamiec->podzespoly[2]);
    fclose(plik);
}

// void	wczytaj_stan_magazynu(): Odtwarzanie stanu przy ponownym uruchomieniu. 

void wczytaj_stan_magazynu() {
    FILE *plik = fopen("stan_magazynu.txt", "r");
    if (plik == NULL) {
        printf("[INFO] Brak pliku stanu magazynu. Używam stanu domyślnego.\n");
        return;
    }

    // Wczytaj dane z pliku
    int wczytane = fscanf(plik, "Jednostki magazynowe: %d\nPodzespoły: X=%d, Y=%d, Z=%d\n",
                          &pamiec->jednostki_magazynowe,
                          &pamiec->podzespoly[0],
                          &pamiec->podzespoly[1],
                          &pamiec->podzespoly[2]);

    if (wczytane != 4) {
        printf("[BŁĄD] Nie udało się wczytać pełnego stanu magazynu z pliku.\n");
        // Przywróć stan domyślny
        pamiec->jednostki_magazynowe = 0;
        pamiec->podzespoly[0] = 0;
        pamiec->podzespoly[1] = 0;
        pamiec->podzespoly[2] = 0;
    } else {
        printf("[INFO] Wczytano stan magazynu z pliku:\n");
        printf("  Jednostki magazynowe: %d\n", pamiec->jednostki_magazynowe);
        printf("  Podzespoły: X=%d, Y=%d, Z=%d\n", pamiec->podzespoly[0], pamiec->podzespoly[1], pamiec->podzespoly[2]);
    }

    fclose(plik);
}

/*
Logika reakcji na polecenia dyrektora (np. zamknięcie magazynu, wznowienie pracy). 

3.	Co udało się zrobić? 
•	Zaimplementowano wszystkie wymagane przypadki użycia: 
o	Płynna dostawa i montaż podzespołów
o	Reakcja na polecenia dyrektora (1-6) z walidacją danych. 
o	Zapisywanie/odtwarzanie stanu magazynu. 
•	Poprawna synchronizacja: Brak „race conditions” dzięki semaforom. 
•	Obsługa błędów: Komunikaty perror dla operacji systemowych. Np. przy zapisie stanu magazynowego do pliku stan_magazynu.txt.
*/
void zapisz_stan_magazynu() {
    FILE *plik = fopen("stan_magazynu.txt", "w");
    if (plik == NULL) {
        perror("Błąd podczas otwierania pliku");
        return;
    }
    fprintf(plik, "Jednostki magazynowe: %d\n", pamiec->jednostki_magazynowe);
    fprintf(plik, "Podzespoły: X=%d, Y=%d, Z=%d\n", pamiec->podzespoly[0], pamiec->podzespoly[1], pamiec->podzespoly[2]);
    fclose(plik);
}


//•	Dodatkowe funkcjonalności: 
//o	Możliwość wznowienia pracy fabryki/magazynu po zatrzymaniu (polecenia 5, 6). 

void proces_dyrektora() {
    char input;
    while (1) {
      
      //....reszta funkcji
            case 5:
                printf("[INFO] Wznawianie pracy magazynu...\n");
            pamiec->magazyn_otwarty = 1;
            break;
            case 6:
                printf("[INFO] Wznawianie pracy fabryki...\n");
            pamiec->fabryka_aktywna = 1;
            break;
        //..... reszta funkcji 
    
}
}

//o	Dodanie kolorów w terminalu dla lepszej czytelności 
/*

Linki do kluczowych funkcji programu: 

- Inicjalizacja pamięci dzielonej:

https://github.com/KamilW-git/PROJEKT-SO---FABRYKA/blob/main/Fabryka/pamiec_dzielona.c#L12-L28

- Obsługa poleceń dyrektora

https://github.com/KamilW-git/PROJEKT-SO---FABRYKA/blob/main/Fabryka/dyrektor.c#L8-L52

- Proces dostawcy

https://github.com/KamilW-git/PROJEKT-SO---FABRYKA/blob/main/Fabryka/dostawca.c#L8-L36

- Proces montera

https://github.com/KamilW-git/PROJEKT-SO---FABRYKA/blob/main/Fabryka/monter.c#L8-L56

- Zapisywanie i wczytywanie stanu magazynu

https://github.com/KamilW-git/PROJEKT-SO---FABRYKA/blob/main/Fabryka/pamiec_dzielona.c#L57-L96

- Semafor – synchronizacja dostępu do magazynu

https://github.com/KamilW-git/PROJEKT-SO---FABRYKA/blob/main/Fabryka/semafor.c#L17-L25

4.	Problemy podczas implementacji 
•	Kolejka komunikatów: 
o	Początkowo polecenia nie docierały do wszystkich procesów (udało się to rozwiązać poprzez wysyłanie wielu komunikatów). 
•	Synchronizacja: 
o	Błędy dostępu do pamięci dzielonej (np. nieaktualny stan magazynu) – naprawione semaforami. 
5. Dodane elementy specjalne 
•	Rozszerzone polecenia: o 5 (wznów magazyn), 6 (wznów fabrykę) – poza wymaganiami projektu. 
•	Logi diagnostyczne: 
o	Komunikaty o stanie magazynu w konsoli (np. DEBUG: podzespoly X=5, Y=5, Z=5). 
•	Elastyczne zarządzanie magazynem: 
o	Dostawcy i monterzy dynamicznie reagują na zmiany stanu magazynu. 
6.	Zauważone problemy z testami 
	• 	Test 2 (przekroczenie pojemności magazynu): 
o 	Czasami brak komunikatu "Brak miejsca!" przy szybkich dostawach (problem z częstotliwością sprawdzania stanu). 
7.	Link do Repozytorium na GitHub: https://github.com/KamilW-git/PROJEKT-SO---FABRYKA 

Podsumowanie: Projekt spełnia wszystkie wymagania obowiązkowe, a dodatkowe funkcjonalności (np. wznowienie pracy magazynu i fabryki) zwiększają jego użyteczność. Głównym wyzwaniem była synchronizacja procesów, ale finalnie działa ona poprawnie. Testy wykazały, że program jest stabilny, choć w skrajnych przypadkach wymaga dodatkowych zabezpieczeń. 
*/