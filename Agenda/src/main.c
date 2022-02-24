#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/compromisso.h"
#include "../headers/agenda.h"

int menuLogin();
int menuAgenda();
int subMenuAgenda(int option);
int menuActiveAgenda();
int menuInsereCompromisso();
int menuRemoveCompromisso();
int menuTodosCompromissos();
int menuRecuperaAgenda();
int menuCompromisso(int id);

int profId = 0;
int agendaId = 0;
int year = 0;

int main()
{
  menuLogin();
  return 0;
}

int menuLogin() //Menu de Selecao de Professor
{
  system("clear");
  printf("Professores:\n");
  for (int i = 0; i < 12; i++)
  {
    printf("%d - %s\n", i + 1, profs[i]); //imprime cada posicao do array profs
  };
  printf("\nDigite o numero referente ao seu nome, ou '0' para sair: ");
  scanf("%d", &profId);
  if (profId)
    menuAgenda();
  else
    exit(0);
}
int menuAgenda() //Menu Criar/Acessar Agenda
{
  int menuOption = 0;
  system("clear");
  printf("Ola, %s\n\n", profs[profId - 1]);
  printf("1 - Criar Agenda\n");
  printf("2 - Acessar Agenda\n\n");
  printf("0 - Trocar professor\n");
  printf("\nDigite o numero referente a opcao desejada: ");
  scanf("%d", &menuOption);

  if (menuOption == 1 || menuOption == 2)
  {
    subMenuAgenda(menuOption);
  }
  if (!menuOption)
  {
    menuLogin();
  }
}
int subMenuAgenda(int option) //SubMenu Criar/Acessar Agenda
{
  system("clear");
  if (option == 1)
  {
    printf("Criar agenda\n");
    printf("\nDigite o ano da agenda: ");
    scanf("%d", &year);
    criaAgenda(agendas, profId, year);
    menuAgenda();
  }
  else
  {
    printf("Agendas Criadas:\n\n");
    printf("+----+------+\n");
    printf("| id | ano  |\n");
    printf("+----+------+\n");
    for (int i = 0; i < 100; i++)
    {
      if (agendas[i].profId == profId)
      {
        printf("| %-2d | %-4d |\n", i + 1, agendas[i].year);
      }
    }
    printf("+----+------+\n\n");
    printf("Digite o Id referende a agenda desejada: ");
    scanf("%d", &agendaId);
    if (agendaId == 0)
    {
      menuAgenda();
    }
    else
    {
      if (agendas[agendaId - 1].profId == profId)
      {
        agendaId--;
        year = agendas[agendaId].year;
        menuActiveAgenda();
      }
      else
      {
        subMenuAgenda(2);
      }
    }
  }
}
int menuActiveAgenda() //Menu da Agenda Selecionada
{
  int option = 0;
  system("clear");
  printf("Menu, %d\n", year);
  printf("1 - Inserir compromisso\n");
  printf("2 - Remover compromisso\n");
  printf("3 - Mostrar todos os compromissos / Acessar um compromisso\n");
  printf("\n");
  printf("4 - Numero de compromissos adiados\n");
  printf("5 - Numero de compromissos cancelados\n");
  printf("6 - Numero de compromissos\n");
  printf("7 - Numero de compromissos apos data\n");
  printf("\n");
  printf("8 - Mostrar compromissos adiados\n");
  printf("9 - Mostrar compromissos cancelados\n");
  printf("10 - Mostrar compromissos a cumprir \n");
  printf("\n");
  printf("11 - Resolver conflitos\n\n");
  printf("0 - Voltar\n");
  printf("\nDigite o numero referente a opcao desejada: ");
  scanf("%d", &option);

  switch (option)
  {
  case 1:
    menuInsereCompromisso();
    break;
  case 2:
    menuRemoveCompromisso();
    break;
  case 3:
    menuTodosCompromissos();
    break;
  case 4:
    retornaNAdiamentos(agendaId);
    break;
  case 5:
    retornaNCancelamentos(agendaId);
    break;
  case 6:
    retornaNCompromissos(agendaId);
    break;
  case 7:
    menuRecuperaAgenda();
    break;
  case 8:
    imprimeCompromissosAdiados(agendaId);
    break;
  case 9:
    imprimeCompromissosCancelados(agendaId);
    break;
  case 10:
    imprimeCompromissosACumprir(agendaId);
    break;
  case 11:
    resolveConflito(agendaId);
    break;
  default:
    menuAgenda();
    break;
  }
  menuActiveAgenda();
}
int menuInsereCompromisso() //Menu de Criacao de Compromisso
{
  int tipo, hora, duracao;
  char nome[100];
  date data;

  system("clear");
  printf("Tipo: \n");
  printf("1 - AULA\n");
  printf("2 - ORIENTACAO\n");
  printf("3 - REUNIAO\n");
  printf("4 - EVENTO\n");
  printf("5 - COMPROMISSO PARTICULAR\n");
  printf("\nDigite o numero referente a opcao desejada: ");
  scanf("%d", &tipo);

  system("clear");
  printf("Tipo: %d\n", tipo);
  printf("Data (dd mm): ");
  scanf("%d %d", &data.day, &data.month);
  printf("Hora (hh): ");
  scanf("%d", &hora);
  printf("Duracao em %s: ", tipo == 4 ? "dias" : "minutos");
  scanf("%d", &duracao);
  printf("Nome do compromisso: ");
  setbuf(stdin, NULL);
  fgets(nome, 100, stdin);
  nome[strcspn(nome, "\n")] = 0;
  insereCompromisso(agendaId, tipo, data, hora, duracao, nome);
  menuActiveAgenda(year);
}
int menuRemoveCompromisso() //Menu de Remocao de Compromisso
{
  int option = 0;
  system("clear");
  printf("+-----------------------------------------------------------------------------------------------------------+\n");
  printf("|                                            REMOVER COMPROMISSO                                            |\n");

  imprimeAgenda(agendaId);

  printf("\nDigite o Id do compromisso que deseja remover, ou digite '0' para voltar: ");
  scanf("%d", &option);
  if (!option)
  {
    menuActiveAgenda();
  }
  else
  {
    removeCompromisso(agendaId, option);
    menuRemoveCompromisso();
  }
}
int menuTodosCompromissos() //Menu de Visualizacao de Compromissos
{
  int option = 0;
  system("clear");
  printf("+-----------------------------------------------------------------------------------------------------------+\n");
  printf("|                                           TODOS OS COMPROMISSOS                                           |\n");
  imprimeAgenda(agendaId);

  printf("\nDigite o numero referente ao Id desejado, ou digite '0' para voltar: ");
  scanf("%d", &option);
  if (!option)
  {
    menuActiveAgenda();
  }
  else
  {
    menuCompromisso(option);
  }
}
int menuRecuperaAgenda() //Menu de Visualizacao de Numero de Compromissos apos Data informada
{
  date data;
  system("clear");
  printf("Digite a data (dd mm): ");
  scanf("%d %d", &data.day, &data.month);
  recuperaAgenda(data, profId, year);
  menuActiveAgenda();
}
int menuCompromisso(int id) //Menu de Edicao de Compromisso
{
  int option = 0;

  system("clear");
  imprimeCompromisso(agendaId, id);
  printf("\n1 - Mostrar Prioridade");
  printf("\n2 - Alterar Prioridade");
  printf("\n3 - Mostrar Status");
  printf("\n4 - Alterar Status");
  printf("\n5 - Alterar se eh adiavel");
  printf("\n\n0 - Voltar");
  printf("\n\nDigite a opcao desejada: ");
  scanf("%d", &option);

  switch (option)
  {
  case 1:
    system("clear");
    setbuf(stdin, NULL);
    retornaPrioridade(agendaId, id);
    printf("\n\nPressione Enter para voltar...");
    getchar();
    menuCompromisso(id);
    break;
  case 2:
    system("clear");
    printf("Digite o numero da nova prioridade: ");
    scanf("%d", &option);
    alteraPrioridade(agendaId, id, option);
    system("clear");
    printf("Prioridade Alterada com Sucesso!");
    printf("\n\nPressione Enter para voltar...");
    setbuf(stdin, NULL);
    getchar();
    menuCompromisso(id);
    break;
  case 3:
    system("clear");
    setbuf(stdin, NULL);
    retornaStatus(agendaId, id);
    printf("\n\nPressione Enter para voltar...");
    getchar();
    menuCompromisso(id);
    break;
  case 4:
    system("clear");
    printf("1 - A SER CUMPRIDO\n");
    printf("2 - ADIADO\n");
    printf("3 - CANCELADO\n\n");
    printf("Digite o numero do novo status: ");
    scanf("%d", &option);
    atribuiStatus(agendaId, id, option);
    system("clear");
    printf("Status Alterado com Sucesso!");
    printf("\n\nPressione Enter para voltar...");
    setbuf(stdin, NULL);
    getchar();
    menuCompromisso(id);
    break;
  case 5:
    system("clear");
    printf("O Compromisso pode ser adiado?\n");
    printf("1 - Verdadeiro\n");
    printf("2 - Falso\n\n");
    printf("Digite o numero da opcao desejada: ");
    scanf("%d", &option);
    eAdiavel(agendaId, id, option);
    system("clear");
    printf("Adiavel Alterado com Sucesso!");
    printf("\n\nPressione Enter para voltar...");
    setbuf(stdin, NULL);
    getchar();
    menuCompromisso(id);
    break;
  default:
    menuTodosCompromissos();
    break;
  }
}
