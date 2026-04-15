#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "escola.h"

void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int validaData(int d, int m, int a) {
    if (a < 1900 || a > 2100) return 0;
    if (m < 1 || m > 12) return 0;
    if (d < 1 || d > 31) return 0;
    if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) return 0;
    if (m == 2) {
        int bissexto = (a % 4 == 0 && a % 100 != 0) || (a % 400 == 0);
        if (d > 29 || (!bissexto && d > 28)) return 0;
    }
    return 1;
}

int validaCPF(char cpf[]) {
    if (strlen(cpf) != 11) return 0;
    for (int i = 0; i < 11; i++) {
        if (cpf[i] < '0' || cpf[i] > '9') return 0;
    }
    int iguais = 1;
    for (int i = 1; i < 11; i++) {
        if (cpf[i] != cpf[0]) iguais = 0;
    }
    if (iguais) return 0;
    int soma = 0;
    for (int i = 0; i < 9; i++) soma += (cpf[i] - '0') * (10 - i);
    int d1 = 11 - (soma % 11);
    if (d1 > 9) d1 = 0;
    if (cpf[9] - '0' != d1) return 0;
    soma = 0;
    for (int i = 0; i < 10; i++) soma += (cpf[i] - '0') * (11 - i);
    int d2 = 11 - (soma % 11);
    if (d2 > 9) d2 = 0;
    if (cpf[10] - '0' != d2) return 0;
    return 1;
}

int existeAluno(int mat, Aluno alunos[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        if (alunos[i].ativo && alunos[i].matricula == mat) return 1;
    }
    return 0;
}

int existeProf(int mat, Professor profs[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        if (profs[i].ativo && profs[i].matricula == mat) return 1;
    }
    return 0;
}

void paraMinusculo(char *dest, char *orig) {
    int i = 0;
    while (orig[i]) {
        dest[i] = tolower(orig[i]);
        i++;
    }
    dest[i] = '\0';
}