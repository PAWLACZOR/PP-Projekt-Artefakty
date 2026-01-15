#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "artefakty.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uzycie: %s nazwa_pliku.txt\n", argv[0]);
        return 1;
    }

    char *nazwaPliku = argv[1];
    Artefakt *archiwum = wczytajZPliku(nazwaPliku);
    int wybor;
    char bufor[MAX_NAME];

    do {
        printf("\n--- GALAKTYCZNE ARCHIWUM ARTEFAKTOW ---\n");
        printf("1. Wyswietl wszystkie\n");
        printf("2. Dodaj nowy artefakt\n");
        printf("3. Usun artefakt\n");
        printf("4. Zapisz i wyjdz\n");
        printf("Wybor: ");

        if (scanf("%d", &wybor) != 1) {
            while(getchar() != '\n'); continue;
        }

        switch (wybor) {
            case 1: wyswietlListe(archiwum); break;
            case 2: archiwum = dodajArtefakt(archiwum); break;
            case 3:
                printf("Podaj nazwe do usuniecia: "); scanf("%s", bufor);
                archiwum = usunArtefakt(archiwum, bufor);
                break;
            case 4: zapiszDoPliku(nazwaPliku, archiwum); break;
        }
    } while (wybor != 4);

    zwolnijPamiec(archiwum);
    return 0;
}
