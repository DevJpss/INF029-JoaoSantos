#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "escola.h"

void cadastrarAluno(Aluno alunos[], int *qtd) {
    if (*qtd >= MAX_ALUNOS) {
        printf("Limite atingido!\n");
        return;
    }
    Aluno a;
    printf("Matricula: ");
    scanf("%d", &a.matricula);
    limpaBuffer();
    
    if (existeAluno(a.matricula, alunos, *qtd)) {
        printf("Matricula ja existe!\n");
        return;
    }
    
    printf("Nome: ");
    fgets(a.nome, 100, stdin);
    a.nome[strcspn(a.nome, "\n")] = '\0';
    
    printf("Sexo (M/F): ");
    scanf(" %c", &a.sexo);
    a.sexo = toupper(a.sexo);
    if (a.sexo != 'M' && a.sexo != 'F') {
        printf("Sexo invalido!\n");
        return;
    }
    
    printf("Data Nascimento (DD MM AAAA): ");
    scanf("%d %d %d", &a.data_nasc.dia, &a.data_nasc.mes, &a.data_nasc.ano);
    if (!validaData(a.data_nasc.dia, a.data_nasc.mes, a.data_nasc.ano)) {
        printf("Data invalida!\n");
        return;
    }
    
    printf("CPF: ");
    scanf("%s", a.cpf);
    if (!validaCPF(a.cpf)) {
        printf("CPF invalido!\n");
        return;
    }
    
    a.ativo = 1;
    alunos[*qtd] = a;
    (*qtd)++;
    printf("Cadastrado com sucesso!\n");
}

void excluirAluno(Aluno alunos[], int qtd) {
    int mat;
    printf("Matricula: ");
    scanf("%d", &mat);
    for (int i = 0; i < qtd; i++) {
        if (alunos[i].ativo && alunos[i].matricula == mat) {
            alunos[i].ativo = 0;
            printf("Excluido!\n");
            return;
        }
    }
    printf("Nao encontrado!\n");
}

void atualizarAluno(Aluno alunos[], int qtd) {
    int mat, idx = -1;
    printf("Matricula: ");
    scanf("%d", &mat);
    limpaBuffer();
    
    for (int i = 0; i < qtd; i++) {
        if (alunos[i].ativo && alunos[i].matricula == mat) idx = i;
    }
    if (idx == -1) {
        printf("Nao encontrado!\n");
        return;
    }
    
    char n_nome[100], n_sexo, n_cpf[15];
    int d, m, a;
    
    printf("Novo Nome: ");
    fgets(n_nome, 100, stdin);
    n_nome[strcspn(n_nome, "\n")] = '\0';
    
    printf("Novo Sexo (M/F): ");
    scanf(" %c", &n_sexo);
    n_sexo = toupper(n_sexo);
    if (n_sexo != 'M' && n_sexo != 'F') {
        printf("Sexo invalido!\n");
        return;
    }
    
    printf("Nova Data (DD MM AAAA): ");
    scanf("%d %d %d", &d, &m, &a);
    if (!validaData(d, m, a)) {
        printf("Data invalida!\n");
        return;
    }
    
    printf("Novo CPF: ");
    scanf("%s", n_cpf);
    if (!validaCPF(n_cpf)) {
        printf("CPF invalido!\n");
        return;
    }
    
    strcpy(alunos[idx].nome, n_nome);
    alunos[idx].sexo = n_sexo;
    alunos[idx].data_nasc.dia = d;
    alunos[idx].data_nasc.mes = m;
    alunos[idx].data_nasc.ano = a;
    strcpy(alunos[idx].cpf, n_cpf);
    printf("Atualizado!\n");
}

void menuAluno(Aluno alunos[], int *qtd) {
    int op;
    do {
        printf("\n1. Novo\n2. Excluir\n3. Atualizar\n0. Voltar\nOpcao: ");
        scanf("%d", &op);
        if (op == 1) cadastrarAluno(alunos, qtd);
        else if (op == 2) excluirAluno(alunos, *qtd);
        else if (op == 3) atualizarAluno(alunos, *qtd);
    } while (op != 0);
}