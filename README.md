# PROJEKT-SO---FABRYKA
 Projekt symuluje działanie fabryki z dwoma stanowiskami produkcyjnymi A i B, wykorzystującymi podzespoły X, Y i Z przechowywane w magazynie o pojemności  𝑀 M. Uwzględnia dostawców i zarządzanie magazynem oraz produkcją z użyciem wielowątkowości lub procesów, zapewniając równoległą realizację zadań.
 
//kompilacja:

gcc main.c dyrektor.c dostawca.c monter.c pamiec_dzielona.c kolejka_komunikatow.c semafor.c -o fabryka
./fabryka
