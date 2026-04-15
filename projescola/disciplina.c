#include <stdio.h>
#include <string.h>
#include "escola.h"

void cadastrarDisciplina(Disciplina discs[], int *qtd, Professor profs[], int qtd_p) {
    if (*qtd >= MAX_DISC) {
        printf("Limite atingido!\n");
        return;
    }
    Disciplina d;
    limpaBuffer();
    printf("Nome: ");
    fgets(d.nome, 50, stdin);
    d.nome[strcspn(d.nome, "\n")] = '\0';
    
    printf("Codigo: ");
    scanf("%s", d.codigo);
    for (int i = 0; i < *qtd; i++) {
        if (discs[i].ativo && strcmp(discs[i].codigo, d.codigo) == 0) {
            printf("Codigo ja existe!\n");
            return;
        }
    }
    
    printf("Semestre: ");
    scanf("%d", &d.semestre);
    if (d.semestre <= 0) {
        printf("Semestre invalido!\n");
        return;
    }
    
    printf("Matricula Professor: ");
    scanf("%d", &d.id_professor);
    
    if (!existeProf(d.id_professor, profs, qtd_p)) {
        printf("Professor nao encontrado!\n");
        return;
    }
    
    d.qtd_alunos = 0;
    d.ativo = 1;
    discs[*qtd] = d;
    (*qtd)++;
    printf("Cadastrada com sucesso!\n");
}

void excluirDisciplina(Disciplina discs[], int qtd) {
    char cod[10];
    printf("Codigo: ");
    scanf("%s", cod);
    for (int i = 0; i < qtd; i++) {
        if (discs[i].ativo && strcmp(discs[i].codigo, cod) == 0) {
            discs[i].ativo = 0;
            printf("Excluida!\n");
            return;
        }
    }
    printf("Nao encontrada!\n");
}

void atualizarDisciplina(Disciplina discs[], int qtd_d) {
    char cod[10];
    int idx = -1;
    printf("Codigo: ");
    scanf("%s", cod);
    limpaBuffer();
    for (int i = 0; i < qtd_d; i++) {
        if (discs[i].ativo && strcmp(discs[i].codigo, cod) == 0) idx = i;
    }
    if (idx == -1) {
        printf("Nao encontrada!\n");
        return;
    }
    printf("Novo Nome: ");
    fgets(discs[idx].nome, 50, stdin);
    discs[idx].nome[strcspn(discs[idx].nome, "\n")] = '\0';
    printf("Atualizada!\n");
}

void alunoDisciplina(Disciplina discs[], int qtd_discs, Aluno alunos[], int qtd_alunos, int tipo) {
    char cod[10];
    int mat, idx_d = -1, idx_a = -1;
    printf("Codigo: ");
    scanf("%s", cod);
    printf("Matricula Aluno: ");
    scanf("%d", &mat);
    
    for (int i = 0; i < qtd_discs; i++) {
        if (discs[i].ativo && strcmp(discs[i].codigo, cod) == 0) idx_d = i;
    }
    for (int i = 0; i < qtd_alunos; i++) {
        if (alunos[i].ativo && alunos[i].matricula == mat) idx_a = i;
    }
    if (idx_d == -1 || idx_a == -1) {
        printf("Disciplina ou Aluno nao encontrados!\n");
        return;
    }
    
    if (tipo == 1) {
        if (discs[idx_d].qtd_alunos >= 60) {
            printf("Limite de vagas atingido!\n");
            return;
        }
        for (int i = 0; i < discs[idx_d].qtd_alunos; i++) {
            if (discs[idx_d].id_alunos[i] == mat) {
                printf("Aluno ja inserido!\n");
                return;
            }
        }
        discs[idx_d].id_alunos[discs[idx_d].qtd_alunos] = mat;
        discs[idx_d].qtd_alunos++;
        printf("Inserido com sucesso!\n");
    } else {
        for (int i = 0; i < discs[idx_d].qtd_alunos; i++) {
            if (discs[idx_d].id_alunos[i] == mat) {
                discs[idx_d].id_alunos[i] = discs[idx_d].id_alunos[discs[idx_d].qtd_alunos - 1];
                discs[idx_d].qtd_alunos--;
                printf("Removido com sucesso!\n");
                return;
            }
        }
        printf("Aluno nao esta na disciplina!\n");
    }
}

void menuDisciplina(Disciplina discs[], int *qtd, Aluno alunos[], int qtd_a, Professor profs[], int qtd_p) {
    int op;
    do {
        printf("\n1. Nova\n2. Excluir\n3. Atualizar\n4. Inserir Aluno\n5. Remover Aluno\n0. Voltar\nOpcao: ");
        scanf("%d", &op);
        if (op == 1) cadastrarDisciplina(discs, qtd, profs, qtd_p);
        else if (op == 2) excluirDisciplina(discs, *qtd);
        else if (op == 3) atualizarDisciplina(discs, *qtd);
        else if (op == 4) alunoDisciplina(discs, *qtd, alunos, qtd_a, 1);
        else if (op == 5) alunoDisciplina(discs, *qtd, alunos, qtd_a, 0);
    } while (op != 0);
}