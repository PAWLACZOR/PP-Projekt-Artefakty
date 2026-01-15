#ifndef ARTEFAKTY_H
#define ARTEFAKTY_H

#define MAX_NAME 100
#define MAX_STATUS 30

typedef struct Artefakt {
    char nazwa[MAX_NAME];
    char pochodzenie[MAX_NAME];
    char cywilizacja[MAX_NAME];
    int poziom_zagrozenia;
    int rok_odkrycia;
    char status[MAX_STATUS];
    struct Artefakt *next;
} Artefakt;

Artefakt* wczytajZPliku(const char *nazwaPliku);
void zapiszDoPliku(const char *nazwaPliku, Artefakt *glowa);
void wyswietlListe(Artefakt *glowa);
void zwolnijPamiec(Artefakt *glowa);


Artefakt* dodajArtefakt(Artefakt *glowa);
Artefakt* usunArtefakt(Artefakt *glowa, char *nazwaDoUsuniecia);

#endif
