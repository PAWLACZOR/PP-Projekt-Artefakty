#include "artefakty.h"

void wyswietlListe(Artefakt *glowa) {
    if (glowa == NULL) {
        printf("\n[INFO] Archiwum jest puste.\n");
        return;
    }
    printf("\n%-20s | %-15s | %-10s | %-10s\n", "Nazwa", "Planeta", "Moc", "Status");
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

    printf("Nazwa: "); scanf("%s", nowy->nazwa);
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
        printf("Nie znaleziono: %s\n", nazwaDoUsuniecia);
        return glowa;
    }
    if (poprzedni == NULL) glowa = temp->next;
    else poprzedni->next = temp->next;
    free(temp);
    printf("Usunieto pomyœlnie.\n");
    return glowa;
}

void wyszukajArtefakt(Artefakt *glowa) {
    char fraza[MAX_NAME];
    printf("Podaj poczatek nazwy (prefix): "); scanf("%s", fraza);
    Artefakt *temp = glowa;
    while (temp) {
        if (strncmp(temp->nazwa, fraza, strlen(fraza)) == 0)
            printf("Znaleziono: %s | Moc: %d | Status: %s\n", temp->nazwa, temp->poziom_zagrozenia, temp->status);
        temp = temp->next;
    }
}

Artefakt* sortujListe(Artefakt *glowa, int tryb) {
    if (!glowa || !glowa->next) return glowa;
    int zamiana;
    do {
        zamiana = 0;
        Artefakt *ptr = glowa;
        while (ptr->next != NULL) {
            int warunek = (tryb == 1) ? strcmp(ptr->nazwa, ptr->next->nazwa) > 0 : ptr->poziom_zagrozenia > ptr->next->poziom_zagrozenia;
            if (warunek) {
                Artefakt temp = *ptr;
                Artefakt *nextPtr = ptr->next;
                *ptr = *nextPtr;
                *nextPtr = temp;
                ptr->next = nextPtr;
                nextPtr->next = temp.next;
                zamiana = 1;
            }
            ptr = ptr->next;
        }
    } while (zamiana);
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
        if (fscanf(f, " %99[^;];%99[^;];%99[^;];%d;%d;%29[^\n]\n", n->nazwa, n->pochodzenie, n->cywilizacja, &n->poziom_zagrozenia, &n->rok_odkrycia, n->status) == 6) {
            n->next = glowa;
            glowa = n;
        } else free(n);
    }
    fclose(f);
    return glowa;
}

void zwolnijPamiec(Artefakt *glowa) {
    while (glowa) {
        Artefakt *temp = glowa;
        glowa = glowa->next;
        free(temp);
    }
}
