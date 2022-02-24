#ifndef AGENDA_H_
#define AGENDA_H_
#include <stdbool.h>

typedef struct date
{
  int day;
  int month;
} date;
typedef struct compromisso
{
  int id;
  int type;
  int priority;
  struct date date;
  int hour;
  int duration;
  char name[100];
  int status;
  int printOrd;
  bool ppable;
} compromisso;
typedef struct agenda
{
  int profId;
  char profName[100];
  int year;
  compromisso compromissos[300];
} agenda;

const char profs[12][100];
const char status[3][20];
const char types[5][25];
const int priorities[5];
const int printOrder[5];
agenda agendas[100];

int criaAgenda(agenda agendas[], int profId, int year);
int recuperaAgenda(date date, int profId, int year);
int insereCompromisso(int agendaId, int type, date date, int hour, int duration, char name[]);
int removeCompromisso(int agendaId, int compromissoId);
int imprimeAgenda(int agendaId);
int resolveConflito(int agendaId);
int retornaNAdiamentos(int agendaId);
int retornaNCancelamentos(int agendaId);
int retornaNCompromissos(int agendaId);
int imprimeCompromissosAdiados(int agendaId);
int imprimeCompromissosCancelados(int agendaId);
int imprimeCompromissosACumprir(int agendaId);

#endif //!AGENDA_H_/