cmake_minimum_required(VERSION 3.10)
project(Fabryka)

set(CMAKE_C_STANDARD 11)


set(SOURCES
        main.c
        dostawca.c
        dyrektor.c
        monter.c
        kolejka_komunikatow.c
        pamiec_dzielona.c
        semafor.c
)


set(HEADERS
        dostawca.h
        dyrektor.h
        monter.h
        kolejka_komunikatow.h
        pamiec_dzielona.h
        semafor.h
)

add_executable(Fabryka ${SOURCES} ${HEADERS})
target_include_directories(Fabryka PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


