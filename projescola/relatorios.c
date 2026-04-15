#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "escola.h"

void listarSimples(Aluno alunos[], int qtd_a, Professor profs[], int qtd_p, Disciplina discs[], int qtd_d) {
    int op;
    printf("Listar: 1.Alunos 2.Professores 3.Disciplinas(sem alunos) 4.Uma Disciplina(com alunos)\nOpcao: ");
    if (scanf("%d", &op) != 1) {
        limpaBuffer();
        printf("Opcao invalida!\n");
        return;
    }
    if (op == 1) {
        for (int i = 0; i < qtd_a; i++) if (alunos[i].ativo) printf("%d - %s\n", alunos[i].matricula, alunos[i].nome);
    } else if (op == 2) {
        for (int i = 0; i < qtd_p; i++) if (profs[i].ativo) printf("%d - %s\n", profs[i].matricula, profs[i].nome);
    } else if (op == 3) {
        for (int i = 0; i < qtd_d; i++) if (discs[i].ativo) printf("%s - %s\n", discs[i].codigo, discs[i].nome);
    } else if (op == 4) {
        char cod[10];
        int encontrou = 0;
        printf("Codigo: ");
        scanf("%s", cod);
        for (int i = 0; i < qtd_d; i++) {
            if (discs[i].ativo && strcmp(discs[i].codigo, cod) == 0) {
                encontrou = 1;
                printf("%s\nAlunos:\n", discs[i].nome);
                for (int j = 0; j < discs[i].qtd_alunos; j++) {
                    int mat = discs[i].id_alunos[j];
                    for (int k = 0; k < qtd_a; k++) {
                        if (alunos[k].ativo && alunos[k].matricula == mat) printf("- %s\n", alunos[k].nome);
                    }
                }
            }
        }
        if (!encontrou) printf("Disciplina nao encontrada!\n");
    }
}

void ordenarGeral(Aluno alunos[], int qtd_a, Professor profs[], int qtd_p, int isProf, int porNome) {
    Aluno tempA[MAX_ALUNOS];
    Professor tempP[MAX_PROFS];
    int t = 0;
    
    if (isProf) {
        for (int i = 0; i < qtd_p; i++) if (profs[i].ativo) tempP[t++] = profs[i];
        for (int i = 0; i < t - 1; i++) {
            for (int j = 0; j < t - i - 1; j++) {
                int troca = 0;
                if (porNome) {
                    if (strcmp(tempP[j].nome, tempP[j + 1].nome) > 0) troca = 1;
                } else {
                    long d1 = tempP[j].data_nasc.ano * 10000 + tempP[j].data_nasc.mes * 100 + tempP[j].data_nasc.dia;
                    long d2 = tempP[j+1].data_nasc.ano * 10000 + tempP[j+1].data_nasc.mes * 100 + tempP[j+1].data_nasc.dia;
                    if (d1 > d2) troca = 1;
                }
                if (troca) { Professor aux = tempP[j]; tempP[j] = tempP[j + 1]; tempP[j + 1] = aux; }
            }
        }
        for (int i = 0; i < t; i++) printf("%s - %02d/%02d/%d\n", tempP[i].nome, tempP[i].data_nasc.dia, tempP[i].data_nasc.mes, tempP[i].data_nasc.ano);
    } else {
        for (int i = 0; i < qtd_a; i++) if (alunos[i].ativo) tempA[t++] = alunos[i];
        for (int i = 0; i < t - 1; i++) {
            for (int j = 0; j < t - i - 1; j++) {
                int troca = 0;
                if (porNome) {
                    if (strcmp(tempA[j].nome, tempA[j + 1].nome) > 0) troca = 1;
                } else {
                    long d1 = tempA[j].data_nasc.ano * 10000 + tempA[j].data_nasc.mes * 100 + tempA[j].data_nasc.dia;
                    long d2 = tempA[j+1].data_nasc.ano * 10000 + tempA[j+1].data_nasc.mes * 100 + tempA[j+1].data_nasc.dia;
                    if (d1 > d2) troca = 1;
                }
                if (troca) { Aluno aux = tempA[j]; tempA[j] = tempA[j + 1]; tempA[j + 1] = aux; }
            }
        }
        for (int i = 0; i < t; i++) printf("%s - %02d/%02d/%d\n", tempA[i].nome, tempA[i].data_nasc.dia, tempA[i].data_nasc.mes, tempA[i].data_nasc.ano);
    }
}

void porSexo(Aluno alunos[], int qtd_a, Professor profs[], int qtd_p, int isProf) {
    char s;
    printf("Sexo (M/F): ");
    scanf(" %c", &s);
    s = toupper(s);
    if (s != 'M' && s != 'F') {
        printf("Sexo invalido!\n");
        return;
    }
    
    if (isProf) {
        for (int i = 0; i < qtd_p; i++) if (profs[i].ativo && profs[i].sexo == s) printf("%s\n", profs[i].nome);
    } else {
        for (int i = 0; i < qtd_a; i++) if (alunos[i].ativo && alunos[i].sexo == s) printf("%s\n", alunos[i].nome);
    }
}

void discExtrapoladas(Disciplina discs[], int qtd_d, Professor profs[], int qtd_p) {
    int encontrou = 0;
    for (int i = 0; i < qtd_d; i++) {
        if (discs[i].ativo && discs[i].qtd_alunos > 40) {
            encontrou = 1;
            char p_nome[100] = "Desc";
            for (int j = 0; j < qtd_p; j++) {
                if (profs[j].ativo && profs[j].matricula == discs[i].id_professor) strcpy(p_nome, profs[j].nome);
            }
            printf("%s - Prof: %s (Vagas: %d)\n", discs[i].nome, p_nome, discs[i].qtd_alunos);
        }
    }
    if (!encontrou) printf("Nenhuma disciplina excedeu 40 vagas.\n");
}

void alunosMenos3Disc(Aluno alunos[], int qtd_a, Disciplina discs[], int qtd_d) {
    int encontrou = 0;
    for (int i = 0; i < qtd_a; i++) {
        if (alunos[i].ativo) {
            int conta = 0;
            for (int j = 0; j < qtd_d; j++) {
                if (discs[j].ativo) {
                    for (int k = 0; k < discs[j].qtd_alunos; k++) {
                        if (discs[j].id_alunos[k] == alunos[i].matricula) conta++;
                    }
                }
            }
            if (conta < 3) {
                printf("%s (%d disc)\n", alunos[i].nome, conta);
                encontrou = 1;
            }
        }
    }
    if (!encontrou) printf("Todos cursam 3 ou mais.\n");
}

void buscarString(Aluno alunos[], int qtd_a, Professor profs[], int qtd_p) {
    char busca[50], buscaMin[50], nomeMin[100];
    int achou = 0;
    
    limpaBuffer();
    printf("Busca (min 3 letras): ");
    fgets(busca, 50, stdin);
    busca[strcspn(busca, "\n")] = '\0';
    
    if (strlen(busca) < 3) {
        printf("Minimo de 3 letras!\n");
        return;
    }
    
    paraMinusculo(buscaMin, busca);
    
    for (int i = 0; i < qtd_a; i++) {
        if (alunos[i].ativo) {
            paraMinusculo(nomeMin, alunos[i].nome);
            if (strstr(nomeMin, buscaMin) != NULL) {
                printf("Aluno: %s\n", alunos[i].nome);
                achou = 1;
            }
        }
    }
    for (int i = 0; i < qtd_p; i++) {
        if (profs[i].ativo) {
            paraMinusculo(nomeMin, profs[i].nome);
            if (strstr(nomeMin, buscaMin) != NULL) {
                printf("Prof: %s\n", profs[i].nome);
                achou = 1;
            }
        }
    }
    if (!achou) printf("Nenhum resultado encontrado!\n");
}

void aniversariantesMes(Aluno alunos[], int qtd_a, Professor profs[], int qtd_p) {
    int mes;
    printf("Digite o mes (1-12): ");
    if (scanf("%d", &mes) != 1 || mes < 1 || mes > 12) {
        limpaBuffer();
        printf("Mes invalido!\n");
        return;
    }
    
    int achou = 0;
    for (int i = 0; i < qtd_a; i++) {
        if (alunos[i].ativo && alunos[i].data_nasc.mes == mes) {
            printf("Aluno: %s (Dia %02d)\n", alunos[i].nome, alunos[i].data_nasc.dia);
            achou = 1;
        }
    }
    for (int i = 0; i < qtd_p; i++) {
        if (profs[i].ativo && profs[i].data_nasc.mes == mes) {
            printf("Prof: %s (Dia %02d)\n", profs[i].nome, profs[i].data_nasc.dia);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhum aniversariante neste mes!\n");
}

void menuRelatorios(Aluno alunos[], int qtd_a, Professor profs[], int qtd_p, Disciplina discs[], int qtd_d) {
    int op;
    do {
        printf("\n1. Listas Simples\n2. A por Nome\n3. A por Data\n4. A por Sexo\n");
        printf("5. P por Nome\n6. P por Data\n7. P por Sexo\n8. <3 Disc\n9. >40 Vagas\n10. Busca\n11. Aniversariantes do Mes\n0. Voltar\nOpcao: ");
        if (scanf("%d", &op) != 1) {
            limpaBuffer();
            op = -1;
            continue;
        }
        
        if (op == 1) listarSimples(alunos, qtd_a, profs, qtd_p, discs, qtd_d);
        else if (op == 2) ordenarGeral(alunos, qtd_a, profs, qtd_p, 0, 1);
        else if (op == 3) ordenarGeral(alunos, qtd_a, profs, qtd_p, 0, 0);
        else if (op == 4) porSexo(alunos, qtd_a, profs, qtd_p, 0);
        else if (op == 5) ordenarGeral(alunos, qtd_a, profs, qtd_p, 1, 1);
        else if (op == 6) ordenarGeral(alunos, qtd_a, profs, qtd_p, 1, 0);
        else if (op == 7) porSexo(alunos, qtd_a, profs, qtd_p, 1);
        else if (op == 8) alunosMenos3Disc(alunos, qtd_a, discs, qtd_d);
        else if (op == 9) discExtrapoladas(discs, qtd_d, profs, qtd_p);
        else if (op == 10) buscarString(alunos, qtd_a, profs, qtd_p);
        else if (op == 11) aniversariantesMes(alunos, qtd_a, profs, qtd_p);
    } while (op != 0);
}