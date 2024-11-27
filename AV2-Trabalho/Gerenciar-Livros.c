#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char titulo[50];
    char autor[50];
    int ano;
} Livro;

int validarCodigo(int codigo) {
    FILE *arquivo = fopen("livros.txt", "r");
    char linha[256];
    
    if (arquivo == NULL) return 1;
    
    while (fgets(linha, 256, arquivo)) {
        int cod_atual = atoi(strtok(linha, ","));
        if (cod_atual == codigo) {
            fclose(arquivo);
            return 0;
        }
    }
    fclose(arquivo);
    return 1;
}

void adicionarLivro() {
    FILE *arquivo;
    Livro livro;
    
    arquivo = fopen("livros.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    do {
        printf("Digite o codigo do livro: ");
        scanf("%d", &livro.codigo);
        getchar();
        
        if (!validarCodigo(livro.codigo)) {
            printf("Codigo ja existe! Tente outro.\n");
        }
    } while (!validarCodigo(livro.codigo));
    
    printf("Digite o titulo do livro: ");
    fgets(livro.titulo, 50, stdin);
    livro.titulo[strcspn(livro.titulo, "\n")] = 0;
    
    printf("Digite o nome do autor: ");
    fgets(livro.autor, 50, stdin);
    livro.autor[strcspn(livro.autor, "\n")] = 0;
    
    printf("Digite o ano de publicacao: ");
    scanf("%d", &livro.ano);
    
    fprintf(arquivo, "%d,%s,%s,%d\n", livro.codigo, livro.titulo, livro.autor, livro.ano);
    fclose(arquivo);
    printf("Livro adicionado com sucesso!\n");
}

void alterarLivro() {
    FILE *arquivo, *temp;
    char linha[256];
    int codigo, encontrado = 0;
    Livro livro;
    int opcao;
    
    printf("Digite o codigo do livro a ser alterado: ");
    scanf("%d", &codigo);
    getchar();
    
    arquivo = fopen("livros.txt", "r");
    temp = fopen("temp.txt", "w");
    
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    while (fgets(linha, 256, arquivo)) {
        char *cod = strtok(linha, ",");
        int cod_atual = atoi(cod);
        
        if (cod_atual == codigo) {
            encontrado = 1;
            printf("\nO que deseja alterar?\n");
            printf("1. Titulo\n2. Autor\n3. Ano de publicacao\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);
            getchar();
            
            livro.codigo = codigo;
            strcpy(livro.titulo, strtok(NULL, ","));
            strcpy(livro.autor, strtok(NULL, ","));
            livro.ano = atoi(strtok(NULL, ","));
            
            switch(opcao) {
                case 1:
                    printf("Digite o novo titulo: ");
                    fgets(livro.titulo, 50, stdin);
                    livro.titulo[strcspn(livro.titulo, "\n")] = 0;
                    break;
                case 2:
                    printf("Digite o novo autor: ");
                    fgets(livro.autor, 50, stdin);
                    livro.autor[strcspn(livro.autor, "\n")] = 0;
                    break;
                case 3:
                    printf("Digite o novo ano: ");
                    scanf("%d", &livro.ano);
                    break;
                default:
                    printf("Opcao invalida!\n");
                    break;
            }
            fprintf(temp, "%d,%s,%s,%d\n", livro.codigo, livro.titulo, livro.autor, livro.ano);
        } else {
            fputs(linha, temp);
        }
    }
    
    fclose(arquivo);
    fclose(temp);
    
    if (encontrado) {
        remove("livros.txt");
        rename("temp.txt", "livros.txt");
        printf("Dados alterados com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Livro nao encontrado!\n");
    }
}

void excluirLivro() {
    FILE *arquivo, *temp;
    char linha[256];
    int codigo;
    int encontrado = 0;
    
    printf("Digite o codigo do livro a ser excluido: ");
    scanf("%d", &codigo);
    
    arquivo = fopen("livros.txt", "r");
    temp = fopen("temp.txt", "w");
    
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    while (fgets(linha, 256, arquivo)) {
        int cod_atual = atoi(strtok(linha, ","));
        if (cod_atual != codigo) {
            fputs(linha, temp);
        } else {
            encontrado = 1;
        }
    }
    
    fclose(arquivo);
    fclose(temp);
    
    if (encontrado) {
        remove("livros.txt");
        rename("temp.txt", "livros.txt");
        printf("Livro excluido com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Livro nao encontrado!\n");
    }
}

void consultarLivro() {
    FILE *arquivo;
    char linha[256];
    int codigo;
    int encontrado = 0;
    
    printf("Digite o codigo do livro: ");
    scanf("%d", &codigo);
    
    arquivo = fopen("livros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    while (fgets(linha, 256, arquivo)) {
        char *cod = strtok(linha, ",");
        if (atoi(cod) == codigo) {
            printf("\nInformacoes do Livro:\n");
            printf("Codigo: %s\n", cod);
            printf("Titulo: %s\n", strtok(NULL, ","));
            printf("Autor: %s\n", strtok(NULL, ","));
            printf("Ano: %s\n", strtok(NULL, ","));
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Livro nao encontrado!\n");
    }
    
    fclose(arquivo);
}

void listarLivros() {
    FILE *arquivo;
    char linha[256];
    
    arquivo = fopen("livros.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    printf("\nCatalogo de Livros:\n");
    printf("Codigo | Titulo | Autor | Ano\n");
    printf("--------------------------------\n");
    
    while (fgets(linha, 256, arquivo)) {
        char *codigo = strtok(linha, ",");
        char *titulo = strtok(NULL, ",");
        char *autor = strtok(NULL, ",");
        char *ano = strtok(NULL, ",");
        
        if (codigo && titulo && autor && ano) {
            printf("%s | %s | %s | %s", codigo, titulo, autor, ano);
        }
    }
    
    fclose(arquivo);
}

int main() {
    int opcao;
    
    do {
        printf("\n=== Sistema de Gerenciamento de Livros ===\n");
        printf("1. Adicionar novo livro\n");
        printf("2. Alterar dados de um livro\n");
        printf("3. Excluir livro\n");
        printf("4. Consultar livro\n");
        printf("5. Listar todos os livros\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                adicionarLivro();
                break;
            case 2:
                alterarLivro();
                break;
            case 3:
                excluirLivro();
                break;
            case 4:
                consultarLivro();
                break;
            case 5:
                listarLivros();
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    
    return 0;
}
