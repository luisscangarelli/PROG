#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char titulo[50];
    char genero[20];
    int ano;
} Filme;

int validarID(int id) {
    FILE *arquivo = fopen("filmes.txt", "r");
    char linha[256];
    
    if (arquivo == NULL) return 1;
    
    while (fgets(linha, 256, arquivo)) {
        int id_atual = atoi(strtok(linha, ","));
        if (id_atual == id) {
            fclose(arquivo);
            return 0;
        }
    }
    fclose(arquivo);
    return 1;
}

void adicionarFilme() {
    FILE *arquivo;
    Filme filme;
    
    arquivo = fopen("filmes.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    do {
        printf("Digite o ID do filme: ");
        scanf("%d", &filme.id);
        getchar();
        
        if (!validarID(filme.id)) {
            printf("ID ja existe! Tente outro.\n");
        }
    } while (!validarID(filme.id));
    
    printf("Digite o titulo do filme: ");
    fgets(filme.titulo, 50, stdin);
    filme.titulo[strcspn(filme.titulo, "\n")] = 0;
    
    printf("Digite o genero do filme: ");
    fgets(filme.genero, 20, stdin);
    filme.genero[strcspn(filme.genero, "\n")] = 0;
    
    printf("Digite o ano de lancamento: ");
    scanf("%d", &filme.ano);
    
    fprintf(arquivo, "%d,%s,%s,%d\n", filme.id, filme.titulo, filme.genero, filme.ano);
    fclose(arquivo);
    printf("Filme adicionado com sucesso!\n");
}

void alterarFilme() {
    FILE *arquivo, *temp;
    char linha[256];
    int id, encontrado = 0;
    Filme filme;
    int opcao;
    
    printf("Digite o ID do filme a ser alterado: ");
    scanf("%d", &id);
    getchar();
    
    arquivo = fopen("filmes.txt", "r");
    temp = fopen("temp.txt", "w");
    
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    while (fgets(linha, 256, arquivo)) {
        char *id_str = strtok(linha, ",");
        int id_atual = atoi(id_str);
        
        if (id_atual == id) {
            encontrado = 1;
            printf("\nO que deseja alterar?\n");
            printf("1. Titulo\n2. Genero\n3. Ano\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);
            getchar();
            
            filme.id = id;
            strcpy(filme.titulo, strtok(NULL, ","));
            strcpy(filme.genero, strtok(NULL, ","));
            filme.ano = atoi(strtok(NULL, ","));
            
            switch(opcao) {
                case 1:
                    printf("Digite o novo titulo: ");
                    fgets(filme.titulo, 50, stdin);
                    filme.titulo[strcspn(filme.titulo, "\n")] = 0;
                    break;
                case 2:
                    printf("Digite o novo genero: ");
                    fgets(filme.genero, 20, stdin);
                    filme.genero[strcspn(filme.genero, "\n")] = 0;
                    break;
                case 3:
                    printf("Digite o novo ano: ");
                    scanf("%d", &filme.ano);
                    break;
                default:
                    printf("Opcao invalida!\n");
                    break;
            }
            fprintf(temp, "%d,%s,%s,%d\n", filme.id, filme.titulo, filme.genero, filme.ano);
        } else {
            fputs(linha, temp);
        }
    }
    
    fclose(arquivo);
    fclose(temp);
    
    if (encontrado) {
        remove("filmes.txt");
        rename("temp.txt", "filmes.txt");
        printf("Dados alterados com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Filme nao encontrado!\n");
    }
}

void excluirFilme() {
    FILE *arquivo, *temp;
    char linha[256];
    int id;
    int encontrado = 0;
    
    printf("Digite o ID do filme a ser excluido: ");
    scanf("%d", &id);
    
    arquivo = fopen("filmes.txt", "r");
    temp = fopen("temp.txt", "w");
    
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    while (fgets(linha, 256, arquivo)) {
        int id_atual = atoi(strtok(linha, ","));
        if (id_atual != id) {
            fputs(linha, temp);
        } else {
            encontrado = 1;
        }
    }
    
    fclose(arquivo);
    fclose(temp);
    
    if (encontrado) {
        remove("filmes.txt");
        rename("temp.txt", "filmes.txt");
        printf("Filme excluido com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Filme nao encontrado!\n");
    }
}

void consultarFilme() {
    FILE *arquivo;
    char linha[256];
    int id;
    int encontrado = 0;
    
    printf("Digite o ID do filme: ");
    scanf("%d", &id);
    
    arquivo = fopen("filmes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    while (fgets(linha, 256, arquivo)) {
        char *id_str = strtok(linha, ",");
        if (atoi(id_str) == id) {
            printf("\nInformacoes do Filme:\n");
            printf("ID: %s\n", id_str);
            printf("Titulo: %s\n", strtok(NULL, ","));
            printf("Genero: %s\n", strtok(NULL, ","));
            printf("Ano: %s\n", strtok(NULL, ","));
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Filme nao encontrado!\n");
    }
    
    fclose(arquivo);
}

void listarFilmes() {
    FILE *arquivo;
    char linha[256];
    
    arquivo = fopen("filmes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    printf("\nAcervo de Filmes:\n");
    printf("ID | Titulo | Genero | Ano\n");
    printf("--------------------------------\n");
    
    while (fgets(linha, 256, arquivo)) {
        char *id = strtok(linha, ",");
        char *titulo = strtok(NULL, ",");
        char *genero = strtok(NULL, ",");
        char *ano = strtok(NULL, ",");
        
        if (id && titulo && genero && ano) {
            printf("%s | %s | %s | %s", id, titulo, genero, ano);
        }
    }
    
    fclose(arquivo);
}

int main() {
    int opcao;
    
    do {
        printf("\n=== Sistema de Controle de Filmes ===\n");
        printf("1. Adicionar novo filme\n");
        printf("2. Alterar dados de um filme\n");
        printf("3. Excluir filme\n");
        printf("4. Consultar filme\n");
        printf("5. Listar todos os filmes\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                adicionarFilme();
                break;
            case 2:
                alterarFilme();
                break;
            case 3:
                excluirFilme();
                break;
            case 4:
                consultarFilme();
                break;
            case 5:
                listarFilmes();
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
