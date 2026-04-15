#ifndef ESCOLA_H
#define ESCOLA_H

#define MAX_ALUNOS 100
#define MAX_PROFS 50
#define MAX_DISC 20

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int matricula;
    char nome[100];
    char sexo;
    Data data_nasc;
    char cpf[15];
    int ativo;
} Aluno;

typedef struct {
    int matricula;
    char nome[100];
    char sexo;
    Data data_nasc;
    char cpf[15];
    int ativo;
} Professor;

typedef struct {
    char nome[50];
    char codigo[10];
    int semestre;
    int id_professor;
    int id_alunos[60];
    int qtd_alunos;
    int ativo;
} Disciplina;

void limpaBuffer();
int validaData(int d, int m, int a);
int validaCPF(char cpf[]);
int existeAluno(int mat, Aluno alunos[], int qtd);
int existeProf(int mat, Professor profs[], int qtd);
void paraMinusculo(char *dest, char *orig);

void menuAluno(Aluno alunos[], int *qtd_alunos);
void menuProfessor(Professor profs[], int *qtd_profs);
void menuDisciplina(Disciplina discs[], int *qtd_discs, Aluno alunos[], int qtd_alunos, Professor profs[], int qtd_profs);
void menuRelatorios(Aluno alunos[], int qtd_alunos, Professor profs[], int qtd_profs, Disciplina discs[], int qtd_discs);
void aniversariantesMes(Aluno alunos[], int qtd_a, Professor profs[], int qtd_p);

#endif