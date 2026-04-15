#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "escola.h"

void cadastrarProfessor(Professor profs[], int *qtd) {
    if (*qtd >= MAX_PROFS) {
        printf("Limite atingido!\n");
        return;
    }
    Professor p;
    printf("Matricula: ");
    scanf("%d", &p.matricula);
    limpaBuffer();
    
    if (existeProf(p.matricula, profs, *qtd)) {
        printf("Matricula ja existe!\n");
        return;
    }
    
    printf("Nome: ");
    fgets(p.nome, 100, stdin);
    p.nome[strcspn(p.nome, "\n")] = '\0';
    
    printf("Sexo (M/F): ");
    scanf(" %c", &p.sexo);
    p.sexo = toupper(p.sexo);
    if (p.sexo != 'M' && p.sexo != 'F') {
        printf("Sexo invalido!\n");
        return;
    }
    
    printf("Data Nascimento (DD MM AAAA): ");
    scanf("%d %d %d", &p.data_nasc.dia, &p.data_nasc.mes, &p.data_nasc.ano);
    if (!validaData(p.data_nasc.dia, p.data_nasc.mes, p.data_nasc.ano)) {
        printf("Data invalida!\n");
        return;
    }
    
    printf("CPF: ");
    scanf("%s", p.cpf);
    if (!validaCPF(p.cpf)) {
        printf("CPF invalido!\n");
        return;
    }
    
    p.ativo = 1;
    profs[*qtd] = p;
    (*qtd)++;
    printf("Cadastrado com sucesso!\n");
}

void excluirProfessor(Professor profs[], int qtd) {
    int mat;
    printf("Matricula: ");
    scanf("%d", &mat);
    for (int i = 0; i < qtd; i++) {
        if (profs[i].ativo && profs[i].matricula == mat) {
            profs[i].ativo = 0;
            printf("Excluido!\n");
            return;
        }
    }
    printf("Nao encontrado!\n");
}

void atualizarProfessor(Professor profs[], int qtd) {
    int mat, idx = -1;
    printf("Matricula: ");
    scanf("%d", &mat);
    limpaBuffer();
    
    for (int i = 0; i < qtd; i++) {
        if (profs[i].ativo && profs[i].matricula == mat) idx = i;
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
    
    strcpy(profs[idx].nome, n_nome);
    profs[idx].sexo = n_sexo;
    profs[idx].data_nasc.dia = d;
    profs[idx].data_nasc.mes = m;
    profs[idx].data_nasc.ano = a;
    strcpy(profs[idx].cpf, n_cpf);
    printf("Atualizado!\n");
}

void menuProfessor(Professor profs[], int *qtd) {
    int op;
    do {
        printf("\n1. Novo\n2. Excluir\n3. Atualizar\n0. Voltar\nOpcao: ");
        scanf("%d", &op);
        if (op == 1) cadastrarProfessor(profs, qtd);
        else if (op == 2) excluirProfessor(profs, *qtd);
        else if (op == 3) atualizarProfessor(profs, *qtd);
    } while (op != 0);
}