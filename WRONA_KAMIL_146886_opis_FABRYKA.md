Fabryka - Opis projektu

//Informacje ogólne

Imię i nazwisko: Kamil Wrona
Numer albumu: 146886
Temat projektu: Fabryka
Link do repozytorium: https://github.com/KamilW-git/PROJEKT-SO---FABRYKA

//Cel projektu

Celem projektu jest symulacja działania fabryki posiadającej dwa stanowiska produkcyjne A i B. Fabryka operuje na podzespołach X, Y i Z, które są przechowywane w magazynie o określonej pojemności 𝑀.
Projekt uwzględnia również dostawców dostarczających podzespoły oraz zarządzanie pracą magazynu i stanowisk produkcyjnych w sposób równoległy, za pomocą wielowątkowości lub procesów.

//Opis działania

//Magazyn:

Przechowuje podzespoły X, Y i Z o różnych jednostkach magazynowych:
Podzespół X zajmuje 1 jednostkę.
Podzespół Y zajmuje 2 jednostki.
Podzespół Z zajmuje 3 jednostki.
Magazyn ma pojemność 𝑀 jednostek.
Podzespoły są przyjmowane z dostaw od niezależnych źródeł w losowych momentach czasowych.

//Stanowiska produkcyjne:

Stanowisko A i stanowisko B montują produkty z podzespołów X, Y i Z.
Po zmontowaniu produktu pobierane są kolejne podzespoły z magazynu.

//Zakończenie pracy:

Magazyn kończy pracę po otrzymaniu polecenia_1 od dyrektora.
Fabryka kończy pracę po otrzymaniu polecenia_2 od dyrektora.
Fabryka i magazyn kończą pracę jednocześnie:
Polecenie_3: Aktualny stan magazynu jest zapisany do pliku i odtwarzany po ponownym uruchomieniu.
Polecenie_4: Stan magazynu nie jest zapisywany; magazyn jest pusty po ponownym uruchomieniu.

//Procesy w systemie:

Procesy reprezentujące dostawców produktów X, Y i Z.
Procesy reprezentujące pracowników na stanowiskach A i B.
Proces zarządzający pracą magazynu i fabryki.

//Specyfikacja techniczna

Język programowania: C
Narzędzia i biblioteki: procesy

//Struktura programu:

Plik główny obsługujący logikę programu.
Moduły obsługujące:
-Magazyn.
-Dostawców.
-Produkcję.

//Testy
Test 1: Normalne działanie fabryki:

Dostawy podzespołów w określonych odstępach czasu.
Produkcja odbywa się płynnie na stanowiskach A i B.
Test 2: Przekroczenie pojemności magazynu:

Dostawcy próbują dostarczyć więcej podzespołów niż wynosi pojemność magazynu.

Test 3: Równoczesne zakończenie pracy fabryki i magazynu:

Testy dla polecenia_3 i polecenia_4.

Test 4: Nieprzewidywalne opóźnienia dostaw:

Dostawy są realizowane w losowych momentach.
