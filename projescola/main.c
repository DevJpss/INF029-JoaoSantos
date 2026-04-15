#include <stdio.h>
#include "escola.h"

int main() {
    Aluno alunos[MAX_ALUNOS];
    Professor profs[MAX_PROFS];
    Disciplina discs[MAX_DISC];
    
    int qtd_alunos = 0;
    int qtd_profs = 0;
    int qtd_discs = 0;
    int opcao;
    
    do {
        printf("\n--- ESCOLA ---\n");
        printf("1. Alunos\n2. Professores\n3. Disciplinas\n4. Relatorios\n0. Sair\nOpcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: menuAluno(alunos, &qtd_alunos); break;
            case 2: menuProfessor(profs, &qtd_profs); break;
            case 3: menuDisciplina(discs, &qtd_discs, alunos, qtd_alunos, profs, qtd_profs); break;
            case 4: menuRelatorios(alunos, qtd_alunos, profs, qtd_profs, discs, qtd_discs); break;
        }
    } while (opcao != 0);
    
    return 0;
}