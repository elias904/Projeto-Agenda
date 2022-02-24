#ifndef COMPROMISSO_H_
#define COMPROMISSO_H_
#include <stdbool.h>
#include "agenda.h"

int ordenaCompromissos(int agendaId);
int inicializaCompromisso(int agendaId, int type, date date, int hour, int duration, char name[]);
int alteraPrioridade(int agendaId, int compromissoId, int priority);
int retornaPrioridade(int agendaId, int compromissoId);
int eAdiavel(int agendaId, int compromissoId, bool flag);
int temConflito(int agendaId, int compromissoId1, int compromissoId2);
int atribuiStatus(int agendaId, int compromissoId, int status);
int retornaStatus(int agendaId, int compromissoId);
int imprimeCompromisso(int agendaId, int compromissoId);

#endif //!COMPROMISSO_H_