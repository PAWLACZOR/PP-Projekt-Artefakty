#include <stdio.h>
#include <stdlib.h>
#include "artefakty.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uruchomienie: %s <plik.txt>\n", argv[0]);
        return 1;
    }

    Artefakt *archiwum = wczytajZPliku(argv[1]);
    int wybor;
    char nazwaBuf[MAX_NAME];

    do {
        printf("\n--- GALAKTYCZNE ARCHIWUM v3.0 ---\n");
        printf("1. Lista | 2. Dodaj | 3. Usun | 4. Szukaj | 5. Sortuj | 6. Wyjdz\n Wybor: ");
        if (scanf("%d", &wybor) != 1) { while(getchar() != '\n'); continue; }

        switch (wybor) {
            case 1: wyswietlListe(archiwum); break;
            case 2: archiwum = dodajArtefakt(archiwum); break;
            case 3: printf("Podaj nazwe: "); scanf("%s", nazwaBuf); archiwum = usunArtefakt(archiwum, nazwaBuf); break;
            case 4: wyszukajArtefakt(archiwum); break;
            case 5: printf("Sortuj wg: 1. Nazwy, 2. Mocy: "); int s; scanf("%d", &s); archiwum = sortujListe(archiwum, s); break;
            case 6: zapiszDoPliku(argv[1], archiwum); break;
        }
    } while (wybor != 6);

    zwolnijPamiec(archiwum);
    return 0;
}
