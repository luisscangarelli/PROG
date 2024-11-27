#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[50];
    char estado[30];
    int populacao;
} Cidade;

int validarCodigo(int codigo) {
    FILE *arquivo = fopen("cidades.txt", "r");
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

void incluirCidade() {
    FILE *arquivo;
    Cidade cidade;
    
    arquivo = fopen("cidades.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    do {
        printf("Digite o codigo da cidade: ");
        scanf("%d", &cidade.codigo);
        getchar();
        
        if (!validarCodigo(cidade.codigo)) {
            printf("Codigo ja existe! Tente outro.\n");
        }
    } while (!validarCodigo(cidade.codigo));
    
    printf("Digite o nome da cidade: ");
    fgets(cidade.nome, 50, stdin);
    cidade.nome[strcspn(cidade.nome, "\n")] = 0;
    
    printf("Digite o estado: ");
    fgets(cidade.estado, 30, stdin);
    cidade.estado[strcspn(cidade.estado, "\n")] = 0;
    
    printf("Digite a populacao: ");
    scanf("%d", &cidade.populacao);
    
    fprintf(arquivo, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
    fclose(arquivo);
    printf("Cidade incluida com sucesso!\n");
}

void alterarDados() {
    FILE *arquivo, *temp;
    char linha[256];
    int codigo, encontrado = 0;
    Cidade cidade;
    int opcao;
    
    printf("Digite o codigo da cidade a ser alterada: ");
    scanf("%d", &codigo);
    getchar();
    
    arquivo = fopen("cidades.txt", "r");
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
            printf("1. Nome\n2. Estado\n3. Populacao\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);
            getchar();
            
            cidade.codigo = codigo;
            strcpy(cidade.nome, strtok(NULL, ","));
            strcpy(cidade.estado, strtok(NULL, ","));
            cidade.populacao = atoi(strtok(NULL, ","));
            
            switch(opcao) {
                case 1:
                    printf("Digite o novo nome: ");
                    fgets(cidade.nome, 50, stdin);
                    cidade.nome[strcspn(cidade.nome, "\n")] = 0;
                    break;
                case 2:
                    printf("Digite o novo estado: ");
                    fgets(cidade.estado, 30, stdin);
                    cidade.estado[strcspn(cidade.estado, "\n")] = 0;
                    break;
                case 3:
                    printf("Digite a nova populacao: ");
                    scanf("%d", &cidade.populacao);
                    break;
                default:
                    printf("Opcao invalida!\n");
                    break;
            }
            fprintf(temp, "%d,%s,%s,%d\n", cidade.codigo, cidade.nome, cidade.estado, cidade.populacao);
        } else {
            fputs(linha, temp);
        }
    }
    
    fclose(arquivo);
    fclose(temp);
    
    if (encontrado) {
        remove("cidades.txt");
        rename("temp.txt", "cidades.txt");
        printf("Dados alterados com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Cidade nao encontrada!\n");
    }
}

void excluirCidade() {
    FILE *arquivo, *temp;
    char linha[256];
    int codigo;
    int encontrado = 0;
    
    printf("Digite o codigo da cidade a ser excluida: ");
    scanf("%d", &codigo);
    
    arquivo = fopen("cidades.txt", "r");
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
        remove("cidades.txt");
        rename("temp.txt", "cidades.txt");
        printf("Cidade excluida com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Cidade nao encontrada!\n");
    }
}

void consultarCidade() {
    FILE *arquivo;
    char linha[256];
    int codigo;
    int encontrado = 0;
    
    printf("Digite o codigo da cidade: ");
    scanf("%d", &codigo);
    
    arquivo = fopen("cidades.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    while (fgets(linha, 256, arquivo)) {
        char *cod = strtok(linha, ",");
        if (atoi(cod) == codigo) {
            printf("\nInformacoes da Cidade:\n");
            printf("Codigo: %s\n", cod);
            printf("Nome: %s\n", strtok(NULL, ","));
            printf("Estado: %s\n", strtok(NULL, ","));
            printf("Populacao: %s habitantes\n", strtok(NULL, ","));
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Cidade nao encontrada!\n");
    }
    
    fclose(arquivo);
}

void listarCidades() {
    FILE *arquivo;
    char linha[256];
    
    arquivo = fopen("cidades.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    printf("\nLista de Cidades:\n");
    printf("Codigo | Nome | Estado | Populacao\n");
    printf("--------------------------------\n");
    
    while (fgets(linha, 256, arquivo)) {
        char *codigo = strtok(linha, ",");
        char *nome = strtok(NULL, ",");
        char *estado = strtok(NULL, ",");
        char *populacao = strtok(NULL, ",");
        
        if (codigo && nome && estado && populacao) {
            printf("%s | %s | %s | %s", codigo, nome, estado, populacao);
        }
    }
    
    fclose(arquivo);
}

int main() {
    int opcao;
    
    do {
        printf("\n=== Sistema de Cadastro de Cidades ===\n");
        printf("1. Incluir cidade\n");
        printf("2. Alterar dados\n");
        printf("3. Excluir cidade\n");
        printf("4. Consultar cidade\n");
        printf("5. Listar cidades\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                incluirCidade();
                break;
            case 2:
                alterarDados();
                break;
            case 3:
                excluirCidade();
                break;
            case 4:
                consultarCidade();
                break;
            case 5:
                listarCidades();
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
