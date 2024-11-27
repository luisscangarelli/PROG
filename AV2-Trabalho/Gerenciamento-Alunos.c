#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 256

typedef struct {
    int matricula;
    char nome[50];
    char curso[30];
    int idade;
} Aluno;

int validarMatricula(int matricula) {
    FILE *arquivo = fopen("alunos.txt", "r");
    char linha[MAX_LINE];
    
    if (arquivo == NULL) return 1; 
    
    while (fgets(linha, MAX_LINE, arquivo)) {
        int mat_atual = atoi(strtok(linha, ","));
        if (mat_atual == matricula) {
            fclose(arquivo);
            return 0; 
        }
    }
    fclose(arquivo);
    return 1; 
}

void incluirAluno() {
    FILE *arquivo;
    Aluno aluno;
    
    arquivo = fopen("alunos.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    do {
        printf("Digite a matrícula do aluno: ");
        scanf("%d", &aluno.matricula);
        getchar(); // Limpar buffer
        
        if (!validarMatricula(aluno.matricula)) {
            printf("Matrícula já existe! Tente outra.\n");
        }
    } while (!validarMatricula(aluno.matricula));
    
    printf("Digite o nome do aluno: ");
    fgets(aluno.nome, 50, stdin);
    aluno.nome[strcspn(aluno.nome, "\n")] = 0;
    
    printf("Digite o curso: ");
    fgets(aluno.curso, 30, stdin);
    aluno.curso[strcspn(aluno.curso, "\n")] = 0;
    
    printf("Digite a idade: ");
    scanf("%d", &aluno.idade);
    
    fprintf(arquivo, "%d,%s,%s,%d\n", aluno.matricula, aluno.nome, aluno.curso, aluno.idade);
    fclose(arquivo);
    printf("Aluno cadastrado com sucesso!\n");
}

void alterarAluno() {
    FILE *arquivo, *temp;
    char linha[MAX_LINE];
    int matricula, encontrado = 0;
    Aluno aluno;
    int opcao;
    
    printf("Digite a matrícula do aluno a ser alterado: ");
    scanf("%d", &matricula);
    getchar();
    
    arquivo = fopen("alunos.txt", "r");
    temp = fopen("temp.txt", "w");
    
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    while (fgets(linha, MAX_LINE, arquivo)) {
        char *mat = strtok(linha, ",");
        int mat_atual = atoi(mat);
        
        if (mat_atual == matricula) {
            encontrado = 1;
            printf("\nO que deseja alterar?\n");
            printf("1. Nome\n2. Curso\n3. Idade\n");
            printf("Escolha uma opção: ");
            scanf("%d", &opcao);
            getchar();
            
            aluno.matricula = matricula;
            strcpy(aluno.nome, strtok(NULL, ","));
            strcpy(aluno.curso, strtok(NULL, ","));
            aluno.idade = atoi(strtok(NULL, ","));
            
            switch(opcao) {
                case 1:
                    printf("Digite o novo nome: ");
                    fgets(aluno.nome, 50, stdin);
                    aluno.nome[strcspn(aluno.nome, "\n")] = 0;
                    break;
                case 2:
                    printf("Digite o novo curso: ");
                    fgets(aluno.curso, 30, stdin);
                    aluno.curso[strcspn(aluno.curso, "\n")] = 0;
                    break;
                case 3:
                    printf("Digite a nova idade: ");
                    scanf("%d", &aluno.idade);
                    break;
                default:
                    printf("Opção inválida!\n");
                    break;
            }
            fprintf(temp, "%d,%s,%s,%d\n", aluno.matricula, aluno.nome, aluno.curso, aluno.idade);
        } else {
            fputs(linha, temp);
        }
    }
    
    fclose(arquivo);
    fclose(temp);
    
    if (encontrado) {
        remove("alunos.txt");
        rename("temp.txt", "alunos.txt");
        printf("Dados alterados com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Aluno não encontrado!\n");
    }
}

void excluirAluno() {
    FILE *arquivo, *temp;
    char linha[MAX_LINE];
    int matricula;
    int encontrado = 0;
    
    printf("Digite a matrícula do aluno a ser excluído: ");
    scanf("%d", &matricula);
    
    arquivo = fopen("alunos.txt", "r");
    temp = fopen("temp.txt", "w");
    
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    while (fgets(linha, MAX_LINE, arquivo)) {
        int mat_atual = atoi(strtok(linha, ","));
        if (mat_atual != matricula) {
            fputs(linha, temp);
        } else {
            encontrado = 1;
        }
    }
    
    fclose(arquivo);
    fclose(temp);
    
    if (encontrado) {
        remove("alunos.txt");
        rename("temp.txt", "alunos.txt");
        printf("Aluno excluído com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Aluno não encontrado!\n");
    }
}

void consultarAluno() {
    FILE *arquivo;
    char linha[MAX_LINE];
    int matricula;
    int encontrado = 0;
    
    printf("Digite a matrícula do aluno: ");
    scanf("%d", &matricula);
    
    arquivo = fopen("alunos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    while (fgets(linha, MAX_LINE, arquivo)) {
        char *mat = strtok(linha, ",");
        if (atoi(mat) == matricula) {
            printf("\nInformações do Aluno:\n");
            printf("Matrícula: %s\n", mat);
            printf("Nome: %s\n", strtok(NULL, ","));
            printf("Curso: %s\n", strtok(NULL, ","));
            printf("Idade: %s\n", strtok(NULL, ","));
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Aluno não encontrado!\n");
    }
    
    fclose(arquivo);
}

// Função para listar todos os alunos
void listarAlunos() {
    FILE *arquivo;
    char linha[MAX_LINE];
    
    arquivo = fopen("alunos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    printf("\nLista de Alunos:\n");
    printf("Matrícula | Nome | Curso | Idade\n");
    printf("--------------------------------\n");
    
    while (fgets(linha, MAX_LINE, arquivo)) {
        char *matricula = strtok(linha, ",");
        char *nome = strtok(NULL, ",");
        char *curso = strtok(NULL, ",");
        char *idade = strtok(NULL, ",");
        
        if (matricula && nome && curso && idade) {
            printf("%s | %s | %s | %s", matricula, nome, curso, idade);
        }
    }
    
    fclose(arquivo);
}

int main() {
    int opcao;
    
    do {
        printf("\n=== Menu do Sistema de Gerenciamento de Alunos ===\n");
        printf("1. Incluir novo aluno\n");
        printf("2. Alterar informações de um aluno\n");
        printf("3. Excluir aluno\n");
        printf("4. Consultar aluno\n");
        printf("5. Listar todos os alunos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                incluirAluno();
                break;
            case 2:
                alterarAluno();
                break;
            case 3:
                excluirAluno();
                break;
            case 4:
                consultarAluno();
                break;
            case 5:
                listarAlunos();
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    
    return 0;
}
