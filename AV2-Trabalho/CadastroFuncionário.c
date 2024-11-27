#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char nome[50];
    char cargo[30];
    int salario;
} Funcionario;

int validarID(int id) {
    FILE *arquivo = fopen("funcionarios.txt", "r");
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

void cadastrarFuncionario() {
    FILE *arquivo;
    Funcionario func;
    
    arquivo = fopen("funcionarios.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    do {
        printf("Digite o ID do funcionario: ");
        scanf("%d", &func.id);
        getchar();
        
        if (!validarID(func.id)) {
            printf("ID ja existe! Tente outro.\n");
        }
    } while (!validarID(func.id));
    
    printf("Digite o nome do funcionario: ");
    fgets(func.nome, 50, stdin);
    func.nome[strcspn(func.nome, "\n")] = 0;
    
    printf("Digite o cargo: ");
    fgets(func.cargo, 30, stdin);
    func.cargo[strcspn(func.cargo, "\n")] = 0;
    
    printf("Digite o salario: ");
    scanf("%d", &func.salario);
    
    fprintf(arquivo, "%d,%s,%s,%d\n", func.id, func.nome, func.cargo, func.salario);
    fclose(arquivo);
    printf("Funcionario cadastrado com sucesso!\n");
}

void alterarFuncionario() {
    FILE *arquivo, *temp;
    char linha[256];
    int id, encontrado = 0;
    Funcionario func;
    int opcao;
    
    printf("Digite o ID do funcionario a ser alterado: ");
    scanf("%d", &id);
    getchar();
    
    arquivo = fopen("funcionarios.txt", "r");
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
            printf("1. Cargo\n2. Salario\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);
            getchar();
            
            func.id = id;
            strcpy(func.nome, strtok(NULL, ","));
            strcpy(func.cargo, strtok(NULL, ","));
            func.salario = atoi(strtok(NULL, ","));
            
            switch(opcao) {
                case 1:
                    printf("Digite o novo cargo: ");
                    fgets(func.cargo, 30, stdin);
                    func.cargo[strcspn(func.cargo, "\n")] = 0;
                    break;
                case 2:
                    printf("Digite o novo salario: ");
                    scanf("%d", &func.salario);
                    break;
                default:
                    printf("Opcao invalida!\n");
                    break;
            }
            fprintf(temp, "%d,%s,%s,%d\n", func.id, func.nome, func.cargo, func.salario);
        } else {
            fputs(linha, temp);
        }
    }
    
    fclose(arquivo);
    fclose(temp);
    
    if (encontrado) {
        remove("funcionarios.txt");
        rename("temp.txt", "funcionarios.txt");
        printf("Dados alterados com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Funcionario nao encontrado!\n");
    }
}

void excluirFuncionario() {
    FILE *arquivo, *temp;
    char linha[256];
    int id;
    int encontrado = 0;
    
    printf("Digite o ID do funcionario a ser excluido: ");
    scanf("%d", &id);
    
    arquivo = fopen("funcionarios.txt", "r");
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
        remove("funcionarios.txt");
        rename("temp.txt", "funcionarios.txt");
        printf("Funcionario excluido com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Funcionario nao encontrado!\n");
    }
}

void consultarFuncionario() {
    FILE *arquivo;
    char linha[256];
    int id;
    int encontrado = 0;
    
    printf("Digite o ID do funcionario: ");
    scanf("%d", &id);
    
    arquivo = fopen("funcionarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    while (fgets(linha, 256, arquivo)) {
        char *id_str = strtok(linha, ",");
        if (atoi(id_str) == id) {
            printf("\nInformacoes do Funcionario:\n");
            printf("ID: %s\n", id_str);
            printf("Nome: %s\n", strtok(NULL, ","));
            printf("Cargo: %s\n", strtok(NULL, ","));
            printf("Salario: R$ %s\n", strtok(NULL, ","));
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Funcionario nao encontrado!\n");
    }
    
    fclose(arquivo);
}

void listarFuncionarios() {
    FILE *arquivo;
    char linha[256];
    
    arquivo = fopen("funcionarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    printf("\nLista de Funcionarios:\n");
    printf("ID | Nome | Cargo | Salario\n");
    printf("--------------------------------\n");
    
    while (fgets(linha, 256, arquivo)) {
        char *id = strtok(linha, ",");
        char *nome = strtok(NULL, ",");
        char *cargo = strtok(NULL, ",");
        char *salario = strtok(NULL, ",");
        
        if (id && nome && cargo && salario) {
            printf("%s | %s | %s | R$ %s", id, nome, cargo, salario);
        }
    }
    
    fclose(arquivo);
}

int main() {
    int opcao;
    
    do {
        printf("\n=== Sistema de Cadastro de Funcionarios ===\n");
        printf("1. Cadastrar novo funcionario\n");
        printf("2. Alterar dados de funcionario\n");
        printf("3. Excluir funcionario\n");
        printf("4. Consultar funcionario\n");
        printf("5. Listar todos os funcionarios\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                cadastrarFuncionario();
                break;
            case 2:
                alterarFuncionario();
                break;
            case 3:
                excluirFuncionario();
                break;
            case 4:
                consultarFuncionario();
                break;
            case 5:
                listarFuncionarios();
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
