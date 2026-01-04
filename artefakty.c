#include <stdio.h>
#include <stdlib.h>
#include "artefakty.h"

void wyswietlListe(Artefakt *glowa) {
    if (!glowa) {
        printf("\nArchiwum jest puste.\n");
        return;
    }
    printf("\n--- LISTA ARTEFAKTOW ---\n");
    // Logika wyswietlania bedzie w Etapie 2
}

void zwolnijPamiec(Artefakt *glowa) {
    Artefakt *temp;
    while (glowa) {
        temp = glowa;
        glowa = glowa->next;
        free(temp);
    }
}
