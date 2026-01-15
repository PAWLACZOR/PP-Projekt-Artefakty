#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "artefakty.h"

void wyswietlListe(Artefakt *glowa) {
    if (glowa == NULL) {
        printf("\n[INFO] Archiwum jest obecnie puste.\n");
        return;
    }
    printf("\n%-20s | %-15s | %-10s | %-10s\n", "Nazwa", "Pochodzenie", "Zagrozenie", "Status");
    printf("----------------------------------------------------------------------\n");
    Artefakt *temp = glowa;
    while (temp != NULL) {
        printf("%-20s | %-15s | %-10d | %-10s\n", temp->nazwa, temp->pochodzenie, temp->poziom_zagrozenia, temp->status);
        temp = temp->next;
    }
}

Artefakt* dodajArtefakt(Artefakt *glowa) {
    Artefakt *nowy = (Artefakt*)malloc(sizeof(Artefakt));
    if (!nowy) return glowa;

    printf("Podaj nazwe: "); scanf("%s", nowy->nazwa);
    printf("Pochodzenie: "); scanf("%s", nowy->pochodzenie);
    printf("Cywilizacja: "); scanf("%s", nowy->cywilizacja);
    printf("Zagrozenie (1-10): "); scanf("%d", &nowy->poziom_zagrozenia);
    printf("Rok odkrycia: "); scanf("%d", &nowy->rok_odkrycia);
    printf("Status: "); scanf("%s", nowy->status);

    nowy->next = glowa;
    return nowy;
}

Artefakt* usunArtefakt(Artefakt *glowa, char *nazwaDoUsuniecia) {
    Artefakt *temp = glowa, *poprzedni = NULL;

    while (temp != NULL && strcmp(temp->nazwa, nazwaDoUsuniecia) != 0) {
        poprzedni = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Nie znaleziono artefaktu o nazwie: %s\n", nazwaDoUsuniecia);
        return glowa;
    }

    if (poprzedni == NULL) glowa = temp->next;
    else poprzedni->next = temp->next;

    free(temp);
    printf("Artefakt %s zostal usuniety.\n", nazwaDoUsuniecia);
    return glowa;
}

void zapiszDoPliku(const char *nazwaPliku, Artefakt *glowa) {
    FILE *f = fopen(nazwaPliku, "w");
    if (!f) return;
    Artefakt *temp = glowa;
    while (temp) {
        fprintf(f, "%s;%s;%s;%d;%d;%s\n", temp->nazwa, temp->pochodzenie, temp->cywilizacja, temp->poziom_zagrozenia, temp->rok_odkrycia, temp->status);
        temp = temp->next;
    }
    fclose(f);
}

Artefakt* wczytajZPliku(const char *nazwaPliku) {
    FILE *f = fopen(nazwaPliku, "r");
    if (!f) return NULL;

    Artefakt *glowa = NULL;
    while (!feof(f)) {
        Artefakt *n = (Artefakt*)malloc(sizeof(Artefakt));
        if (fscanf(f, " %99[^;];%99[^;];%99[^;];%d;%d;%29[^\n]\n",
            n->nazwa, n->pochodzenie, n->cywilizacja,
            &n->poziom_zagrozenia, &n->rok_odkrycia, n->status) == 6) {
            n->next = glowa;
            glowa = n;
        } else {
            free(n);
        }
    }
    fclose(f);
    return glowa;
}

void zwolnijPamiec(Artefakt *glowa) {
    Artefakt *temp;
    while (glowa != NULL) {
        temp = glowa;
        glowa = glowa->next;
        free(temp);
    }
}
