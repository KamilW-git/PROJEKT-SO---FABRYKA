cmake_minimum_required(VERSION 3.30)
project(Desktop C)

set(CMAKE_C_STANDARD 11)

add_executable(Desktop main.c monter.c semafor.c utils.c pamiec_dzielona.c kolejka_komunikatow.c dyrektor.c dostawca.c)
