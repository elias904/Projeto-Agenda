#include "../headers/agenda.h"
#include "../headers/compromisso.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

const char profs[12][100] = {"Alexandre Bittencourt", "Charles Figueredo", "Daniel Luiz", "Edimilson Batista", "Elder Jose", "Elverton Carvalho", "Flavio Luiz", "Matheus Carvalho", "Milene Barbosa", "Rafael Sachetto", "Sofia Larissa", "Vinicius da Fonseca"};
const char status[3][20] = {"A SER CUMPRIDO", "ADIADO", "CANCELADO"};
const char types[5][25] = {"AULA", "ORIENTACAO", "REUNIAO", "EVENTO", "COMPROMISSO PARTICULAR"};
const int priorities[5] = {2, 1, 4, 3, 2}; //prioridades dos compromissos: aula=2, orientacao=1, reuniao=4, evento=3, compromissoParicular=2
const int printOrder[5] = {3, 4, 2, 1, 5}; //ordem de impressao: aula=3, orientacao=4, reuniao=2, evento=1, compromissoParticular=5

int criaAgenda(agenda agendas[], int profId, int year)
{
	//Procura por uma Agenda que nao possua um Id de Professor 
	//e preenche com as informacoes passadas como parametro
	for (int i = 0; i < 100; i++)
	{
		if (!agendas[i].profId)
		{
			agendas[i].profId = profId;
			strcpy(agendas[i].profName, profs[profId - 1]);
			agendas[i].year = year;
			break;
		}
	}
}

int recuperaAgenda(date date, int profId, int year)
{
	int cont = 0;
	for (int i = 0; i < 100; i++)
	{
		if (agendas[i].profId == profId && agendas[i].year == year) //Procura pela Agenda que possui o ProfId e Ano passados como parametro
		{
			for (int j = 0; j < 300; j++)
			{
				if (agendas[i].compromissos[j].id) //procura por compromissos que possuem um Id != 0
				{
					if (agendas[i].compromissos[j].date.month > date.month) //Se o mes do compromisso for maior que o mes informado, entao adiciona 1 no contador de compromissos
					{
						cont++;
					}
					else if (agendas[i].compromissos[j].date.month == date.month && agendas[i].compromissos[j].date.day >= date.day) // caso o mes seja igual verifica de o dia é maior
					{
						cont++;
					}
				}
			}
			system("clear");
			printf("Professor: %s\n", agendas[i].profName);
			printf("Ano: %d\n", agendas[i].year);
			printf("Numero de compromissos: %d\n\n", cont);
			printf("Pressione Enter para voltar...");
			setbuf(stdin, NULL);
			getchar();
		}
	}
}

int insereCompromisso(int agendaId, int type, date date, int hour, int duration, char name[])
{
	int id = inicializaCompromisso(agendaId, type, date, hour, duration, name); //id recebe o retorno de inicializaCompromisso
	if (id) //caso o id seja > 0, entao o compromisso foi craido com sucesso
	{
		printf("Compromisso de Id %d Criado\n\n", id);
		printf("Pressione Enter para continuar...\n");
		setbuf(stdin, NULL);
		getchar();
	}
	else //caso id seja  == 0 é porque todos as posicoes de compromisso ja foram preenchidas
	{
		printf("Erro: agenda cheia\n\n");
		printf("Pressione Enter para continuar...\n");
		setbuf(stdin, NULL);
		getchar();
	}
}

int removeCompromisso(int agendaId, int compromissoId)
{
	for (int i = 0; i < 300; i++)
	{
		if (agendas[agendaId].compromissos[i].id == compromissoId) //A partir do Id de Agenda informado, procura pelo compromisso com o mesmo id Informado
		{
			agendas[agendaId].compromissos[i].id = 0; //Muda o Id do compromisso encontrado para 0. Assim, na hora de inserir ele sera considerado como uma posicao vazia
		}
	}
}

int imprimeAgenda(int agendaId)
{
	ordenaCompromissos(agendaId); //ordena os compromissos na ordem informada no pdf: data->prioridade->...
	printf("+-----+------------------------+---------------+----------+----------------------+---------+----------------+\n");
	printf("| id  | tipo                   | data - hora   | duracao  | nome                 | adiavel | status         |\n");
	printf("+-----+------------------------+---------------+----------+----------------------+---------+----------------+\n");
	for (int j = 0; j < 300; j++)
	{
		if (agendas[agendaId].compromissos[j].id) //Executa um printf em cada compromisso com Id > 0 encontrado
		{
			printf("| %-3d ", agendas[agendaId].compromissos[j].id);
			printf("| %-22s ", types[agendas[agendaId].compromissos[j].type - 1]);
			printf("| %2d/%2d - %2d:00 ", agendas[agendaId].compromissos[j].date.day, agendas[agendaId].compromissos[j].date.month, agendas[agendaId].compromissos[j].hour);
			printf("| %3d %-4s ", agendas[agendaId].compromissos[j].duration, agendas[agendaId].compromissos[j].type == 4 ? "dias" : "min"); //caso o compromisso seja um evento, mostrar dias em vez de minutos
			printf("| %-20s ", agendas[agendaId].compromissos[j].name);
			printf("| %-7s ", agendas[agendaId].compromissos[j].ppable ? "true" : "false");
			printf("| %-14s |\n", status[agendas[agendaId].compromissos[j].status - 1]);
		}
	}
	printf("+-----+------------------------+---------------+----------+----------------------+---------+----------------+\n\n");
}

int resolveConflito(int agendaId)
{
	int id1 = 0;
	int id2 = 0;
	int hasConflict = 0;
	int isResolved = 0;

	while (!isResolved) //executa até que todos os conflitos tenham sido resolvidos
	{
		isResolved = 1;
		for (int i = 0; i < 299; i++)
		{
			if (agendas[agendaId].compromissos[i].id && agendas[agendaId].compromissos[i].status == 1) //procura por compromissos com id > 0 e status A CUMPRIR
			{
				if (!id1) //caso id1 == 0, recebe i + 1 (adicionamos + 1, pois é necessario que o id seja > 0)
					id1 = i + 1;
				else //caso id1 ja tenha um valor > 0, entao id2 ira receber i + 1
					id2 = i + 1;

				if (id1 && id2) //quando id1 e id2 possuirem valores > 0, verifica se ha conflitos entre os 2 ids
				{
					id1--; //removemos o + 1 adicionados anteriormente
					id2--;
					hasConflict = temConflito(agendaId, id1, id2);// verifica se ha conflito entre os ids passados
					if (hasConflict) //caso tenha conflito...
					{
						compromisso *comp1 = &agendas[agendaId].compromissos[id1];
						compromisso *comp2 = &agendas[agendaId].compromissos[id2]; 
						if (comp1->priority > comp2->priority) //Se a prioridade de 1 for maior (quanto maior, menos prioritario) que 2
						{
							if (!comp1->ppable || comp1->type == 1 || comp1->type == 4) //caso comp1 nao seja adiavel, seja aula ou evento. comp1 sera cancelado, se nao, sera adiado
							{
								comp1->status = 3; //cancela o compromisso 1
							}
							else
							{
								comp1->status = 2; //adia o compromisso 1
							}
							isResolved = 0;
						}
						else if (comp1->priority < comp2->priority) //se a prioridade 1 for menor que 2, entao faz o mesmo que acima, para o compromisso2
						{
							if (!comp2->ppable || comp2->type == 1 || comp2->type == 4)
							{
								comp2->status = 3; //cancela o compromisso 2
							}
							else
							{
								comp2->status = 2; //adia o compromisso 2
							}
							isResolved = 0;
						}
						else
						{
							if (comp1->printOrd > comp2->printOrd) //caso a prioridade seja igual, verifica pela a ordem de impressao
							{
								if (!comp1->ppable || comp1->type == 1 || comp1->type == 4)
								{
									comp1->status = 3; //cancela o compromisso 1
								}
								else
								{
									comp1->status = 2; //adia o compromisso 1
								}
								isResolved = 0;
							}
							else if (comp1->printOrd < comp2->printOrd)
							{
								if (!comp2->ppable || comp2->type == 1 || comp2->type == 4)
								{
									comp2->status = 3; //cancela o compromisso 2
								}
								else
								{
									comp2->status = 2; //adia o compromisso 2
								}
								isResolved = 0;
							}
						}
					}
					else //caso nao tenha conflito reduz 1 de i, para poder continuar de onde parou o id2
					{
						i--; 
					}

					id1 = 0; //zera os ids para pegar 2 novos ids
					id2 = 0;
				}
			}
		}
	}
	system("clear");
	printf("Conflitos Resolvidos!!\n");
	printf("\nPressione Enter para voltar...");
	setbuf(stdin, NULL);
	getchar();
}

int retornaNAdiamentos(int agendaId)
{
	int count = 0;
	for (int i = 0; i < 300; i++)
	{
		if (agendas[agendaId].compromissos[i].id && agendas[agendaId].compromissos[i].status == 2) //A cada compromisso com status == 2, adiciona 1 no contador
		{
			count++;
		}
	}
	system("clear");
	printf("Voce possui %d compromissos Adiados em sua Agenda\n", count);
	printf("\nPressione Enter para voltar...\n");
	setbuf(stdin, NULL);
	getchar();
}

int retornaNCancelamentos(int agendaId)
{
	int count = 0;
	for (int i = 0; i < 300; i++)
	{
		if (agendas[agendaId].compromissos[i].id && agendas[agendaId].compromissos[i].status == 3) //A cada compromisso com status == 3, adiciona 1 no contador
		{
			count++;
		}
	}
	system("clear");
	printf("Voce possui %d compromissos Cancelados em sua Agenda\n", count);
	printf("\nPressione Enter para voltar...\n");
	setbuf(stdin, NULL);
	getchar();
}

int retornaNCompromissos(int agendaId)
{
	int count = 0;
	for (int i = 0; i < 300; i++)
	{
		if (agendas[agendaId].compromissos[i].id) //A cada compromisso com id > 0, adiciona 1 no contador
		{
			count++;
		}
	}
	system("clear");
	printf("Voce possui %d Compromissos em sua Agenda\n", count);
	printf("\nPressione Enter para voltar...\n");
	setbuf(stdin, NULL);
	getchar();
}

int imprimeCompromissosAdiados(int agendaId)
{
	system("clear");
	ordenaCompromissos(agendaId);
	printf("+-----------------------------------------------------------------------------------------------------------+\n");
	printf("|                                           COMPROMISSOS ADIADOS                                            |\n");
	printf("+-----+------------------------+---------------+----------+----------------------+---------+----------------+\n");
	printf("| id  | tipo                   | data - hora   | duracao  | nome                 | adiavel | status         |\n");
	printf("+-----+------------------------+---------------+----------+----------------------+---------+----------------+\n");
	for (int i = 0; i < 300; i++)
	{
		if (agendas[agendaId].compromissos[i].id && agendas[agendaId].compromissos[i].status == 2) //Imprime cada compromisso com id > 0 e status == 2
		{
			printf("| %-3d ", agendas[agendaId].compromissos[i].id);
			printf("| %-22s ", types[agendas[agendaId].compromissos[i].type - 1]);
			printf("| %2d/%2d - %2d:00 ", agendas[agendaId].compromissos[i].date.day, agendas[agendaId].compromissos[i].date.month, agendas[agendaId].compromissos[i].hour);
			printf("| %3d %4s ", agendas[agendaId].compromissos[i].duration, agendas[agendaId].compromissos[i].type == 4 ? "dias" : "min");
			printf("| %-20s ", agendas[agendaId].compromissos[i].name);
			printf("| %-7s ", agendas[agendaId].compromissos[i].ppable ? "true" : "false");
			printf("| %-14s |\n", status[agendas[agendaId].compromissos[i].status - 1]);
		}
	}
	printf("+-----+------------------------+---------------+----------+----------------------+---------+----------------+\n\n");
	printf("\nPressione Enter para voltar...\n");
	setbuf(stdin, NULL);
	getchar();
}

int imprimeCompromissosCancelados(int agendaId)
{
	system("clear");
	ordenaCompromissos(agendaId);
	printf("+-----------------------------------------------------------------------------------------------------------+\n");
	printf("|                                         COMPROMISSOS CANCELADOS                                           |\n");
	printf("+-----+------------------------+---------------+----------+----------------------+---------+----------------+\n");
	printf("| id  | tipo                   | data - hora   | duracao  | nome                 | adiavel | status         |\n");
	printf("+-----+------------------------+---------------+----------+----------------------+---------+----------------+\n");
	for (int i = 0; i < 300; i++)
	{
		if (agendas[agendaId].compromissos[i].id && agendas[agendaId].compromissos[i].status == 3) //Imprime cada compromisso com id > 0 e status == 3
		{
			printf("| %-3d ", agendas[agendaId].compromissos[i].id);
			printf("| %-22s ", types[agendas[agendaId].compromissos[i].type - 1]);
			printf("| %2d/%2d - %2d:00 ", agendas[agendaId].compromissos[i].date.day, agendas[agendaId].compromissos[i].date.month, agendas[agendaId].compromissos[i].hour);
			printf("| %3d %4s ", agendas[agendaId].compromissos[i].duration, agendas[agendaId].compromissos[i].type == 4 ? "dias" : "min");
			printf("| %-20s ", agendas[agendaId].compromissos[i].name);
			printf("| %-7s ", agendas[agendaId].compromissos[i].ppable ? "true" : "false");
			printf("| %-14s |\n", status[agendas[agendaId].compromissos[i].status - 1]);
		}
	}
	printf("+-----+------------------------+---------------+----------+----------------------+---------+----------------+\n\n");
	printf("\nPressione Enter para voltar...\n");
	setbuf(stdin, NULL);
	getchar();
}

int imprimeCompromissosACumprir(int agendaId)
{
	system("clear");
	ordenaCompromissos(agendaId);
	printf("+-----------------------------------------------------------------------------------------------------------+\n");
	printf("|                                          COMPROMISSOS A CUMPRIR                                           |\n");
	printf("+-----+------------------------+---------------+----------+----------------------+---------+----------------+\n");
	printf("| id  | tipo                   | data - hora   | duracao  | nome                 | adiavel | status         |\n");
	printf("+-----+------------------------+---------------+----------+----------------------+---------+----------------+\n");
	for (int i = 0; i < 300; i++)
	{
		if (agendas[agendaId].compromissos[i].id && agendas[agendaId].compromissos[i].status == 1) //Imprime cada compromisso com id > 0 e status == 1
		{
			printf("| %-3d ", agendas[agendaId].compromissos[i].id);
			printf("| %-22s ", types[agendas[agendaId].compromissos[i].type - 1]);
			printf("| %2d/%2d - %2d:00 ", agendas[agendaId].compromissos[i].date.day, agendas[agendaId].compromissos[i].date.month, agendas[agendaId].compromissos[i].hour);
			printf("| %3d %4s ", agendas[agendaId].compromissos[i].duration, agendas[agendaId].compromissos[i].type == 4 ? "dias" : "min");
			printf("| %-20s ", agendas[agendaId].compromissos[i].name);
			printf("| %-7s ", agendas[agendaId].compromissos[i].ppable ? "true" : "false");
			printf("| %-14s |\n", status[agendas[agendaId].compromissos[i].status - 1]);
		}
	}
	printf("+-----+------------------------+---------------+----------+----------------------+---------+----------------+\n\n");
	printf("\nPressione Enter para voltar...\n");
	setbuf(stdin, NULL);
	getchar();
}
