#include "../headers/compromisso.h"
#include <stdio.h>
#include <string.h>

int ordenaCompromissos(int agendaId)
{
    int isOrd = 0;

    while (!isOrd) //executa enquanto os compromissos nao forem ordenados
    {
        isOrd = 1;
        for (int i = 0; i < 299; i++)
        {
            //caso o mes[i] seja > mes[i+1]
            if (agendas[agendaId].compromissos[i].date.month > agendas[agendaId].compromissos[i + 1].date.month && agendas[agendaId].compromissos[i + 1].id)
            {
                //Inverte mes[i] com mes[i+1]
                compromisso aux = agendas[agendaId].compromissos[i];
                agendas[agendaId].compromissos[i] = agendas[agendaId].compromissos[i + 1];
                agendas[agendaId].compromissos[i + 1] = aux;
                isOrd = 0;
            }
            //se mes[i] == mes[i+1] entao compara os dias
            else if (agendas[agendaId].compromissos[i].date.month == agendas[agendaId].compromissos[i + 1].date.month && agendas[agendaId].compromissos[i + 1].id)
            {
                if (agendas[agendaId].compromissos[i].date.day > agendas[agendaId].compromissos[i + 1].date.day)
                {
                    compromisso aux = agendas[agendaId].compromissos[i];
                    agendas[agendaId].compromissos[i] = agendas[agendaId].compromissos[i + 1];
                    agendas[agendaId].compromissos[i + 1] = aux;
                    isOrd = 0;
                }
                //se os dias forem iguais, entao compara as horas
                else if (agendas[agendaId].compromissos[i].date.day == agendas[agendaId].compromissos[i + 1].date.day)
                {
                    if (agendas[agendaId].compromissos[i].hour > agendas[agendaId].compromissos[i + 1].hour)
                    {
                        compromisso aux = agendas[agendaId].compromissos[i];
                        agendas[agendaId].compromissos[i] = agendas[agendaId].compromissos[i + 1];
                        agendas[agendaId].compromissos[i + 1] = aux;
                        isOrd = 0;
                    }
                    //se as horas forem iguais, entao compara a prioridade
                    else if (agendas[agendaId].compromissos[i].hour == agendas[agendaId].compromissos[i + 1].hour)
                    {
                        if (agendas[agendaId].compromissos[i].priority > agendas[agendaId].compromissos[i + 1].priority)
                        {
                            compromisso aux = agendas[agendaId].compromissos[i];
                            agendas[agendaId].compromissos[i] = agendas[agendaId].compromissos[i + 1];
                            agendas[agendaId].compromissos[i + 1] = aux;
                            isOrd = 0;
                        }
                        //se as prioridades forem iguais, entao compara a order de impressao
                        else if (agendas[agendaId].compromissos[i].priority == agendas[agendaId].compromissos[i + 1].priority)
                        {
                            if (agendas[agendaId].compromissos[i].printOrd > agendas[agendaId].compromissos[i + 1].printOrd)
                            {
                                compromisso aux = agendas[agendaId].compromissos[i];
                                agendas[agendaId].compromissos[i] = agendas[agendaId].compromissos[i + 1];
                                agendas[agendaId].compromissos[i + 1] = aux;
                                isOrd = 0;
                            }
                        }
                    }
                }
            }
        }
    }
}

int inicializaCompromisso(int agendaId, int type, date date, int hour, int duration, char name[])
{
    for (int j = 0; j < 300; j++)
    {
        if (!agendas[agendaId].compromissos[j].id) //edita o compromisso na primeira posicao com id == 0 encontrada
        {
            agendas[agendaId].compromissos[j].id = j + 1; //para que o id nunca seja 0, adiciona +1 ao i
            agendas[agendaId].compromissos[j].type = type;
            agendas[agendaId].compromissos[j].hour = hour;
            agendas[agendaId].compromissos[j].duration = duration;
            strcpy(agendas[agendaId].compromissos[j].name, name);
            agendas[agendaId].compromissos[j].date.day = date.day;
            agendas[agendaId].compromissos[j].date.month = date.month;
            agendas[agendaId].compromissos[j].status = 1;
            agendas[agendaId].compromissos[j].priority = priorities[type - 1]; //recebe o valor do array priorities referente a posicao type - 1
            agendas[agendaId].compromissos[j].printOrd = printOrder[type - 1]; //recebe o valor do array printOrder referente a posicao type - 1
            agendas[agendaId].compromissos[j].ppable = false;
            ordenaCompromissos(agendaId); //ordena os compromissos
            return (j + 1);               //retorna o id
        }
    }
    return (0); //caso nao encontre nenhum id == 0, retorna 0
}

int alteraPrioridade(int agendaId, int compromissoId, int priority)
{
    for (int i = 0; i < 300; i++)
    {
        if (agendas[agendaId].compromissos[i].id == compromissoId) // procura pelo Comprmisso Id passado como parametro e altera a prioridade
        {
            agendas[agendaId].compromissos[i].priority = priority;
        }
    }
}

int retornaPrioridade(int agendaId, int compromissoId)
{
    for (int i = 0; i < 300; i++)
    {
        if (agendas[agendaId].compromissos[i].id == compromissoId) // procura pelo Comprmisso Id passado como parametro e imprime a prioridade
        {
            printf("\nPrioridade: %d", agendas[agendaId].compromissos[i].priority);
        }
    }
}

int eAdiavel(int agendaId, int compromissoId, bool flag)
{
    for (int i = 0; i < 300; i++)
    {
        if (agendas[agendaId].compromissos[i].id == compromissoId) // procura pelo Comprmisso Id passado como parametro e altera se é adiavel
        {
            if (flag == 1)
            {
                agendas[agendaId].compromissos[i].ppable = true;
            }
            else if (flag == 2)
            {
                agendas[agendaId].compromissos[i].ppable = false;
            }
        }
    }
}

int temConflito(int agendaId, int compromissoId1, int compromissoId2)
{
    //compara o mes, dia e hora. Caso seja igual, retorna 1, se nao 0
    if (agendas[agendaId].compromissos[compromissoId1].date.month == agendas[agendaId].compromissos[compromissoId2].date.month)
    {
        if (agendas[agendaId].compromissos[compromissoId1].date.day == agendas[agendaId].compromissos[compromissoId2].date.day && agendas[agendaId].compromissos[compromissoId1].hour == agendas[agendaId].compromissos[compromissoId2].hour)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int atribuiStatus(int agendaId, int compromissoId, int status)
{
    for (int i = 0; i < 300; i++)
    {
        if (agendas[agendaId].compromissos[i].id == compromissoId) // procura pelo Comprmisso Id passado como parametro e altera o status
        {
            agendas[agendaId].compromissos[i].status = status;
        }
    }
}

int retornaStatus(int agendaId, int compromissoId)
{
    for (int i = 0; i < 300; i++)
    {
        if (agendas[agendaId].compromissos[i].id == compromissoId) // procura pelo Comprmisso Id passado como parametro e imprime o status
        {
            printf("\nStatus: %s", status[agendas[agendaId].compromissos[i].status - 1]);
        }
    }
}

int imprimeCompromisso(int agendaId, int compromissoId)
{
    for (int i = 0; i < 300; i++)
    {
        if (agendas[agendaId].compromissos[i].id == compromissoId)
        {
            printf("+-----+------------------------+---------------+----------+----------------------+---------+----------------+\n");
            printf("| id  | tipo                   | data - hora   | duracao  | nome                 | adiavel | status         |\n");
            printf("+-----+------------------------+---------------+----------+----------------------+---------+----------------+\n");
            printf("| %-3d ", agendas[agendaId].compromissos[i].id);
            printf("| %-22s ", types[agendas[agendaId].compromissos[i].type - 1]);
            printf("| %2d/%2d - %2d:00 ", agendas[agendaId].compromissos[i].date.day, agendas[agendaId].compromissos[i].date.month, agendas[agendaId].compromissos[i].hour);
            printf("| %3d %4s ", agendas[agendaId].compromissos[i].duration, agendas[agendaId].compromissos[i].type == 4 ? "dias" : "min");
            printf("| %-20s ", agendas[agendaId].compromissos[i].name);
            printf("| %-7s ", agendas[agendaId].compromissos[i].ppable ? "true" : "false");
            printf("| %-14s |\n", status[agendas[agendaId].compromissos[i].status - 1]);
            printf("+-----+------------------------+---------------+----------+----------------------+---------+----------------+\n");
        }
    }
}