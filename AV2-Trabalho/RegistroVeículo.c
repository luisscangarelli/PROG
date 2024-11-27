#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char modelo[50];
    char placa[10];
    int ano;
} Veiculo;

int validarID(int id) {
    FILE *arquivo = fopen("veiculos.txt", "r");
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

int validarPlaca(char *placa) {
    FILE *arquivo = fopen("veiculos.txt", "r");
    char linha[256], *placa_atual;
    char temp[256];
    
    if (arquivo == NULL) return 1;
    
    while (fgets(linha, 256, arquivo)) {
        strcpy(temp, linha);
        strtok(temp, ",");
        strtok(NULL, ",");
        placa_atual = strtok(NULL, ",");
        
        if (strcmp(placa_atual, placa) == 0) {
            fclose(arquivo);
            return 0;
        }
    }
    fclose(arquivo);
    return 1;
}

void adicionarVeiculo() {
    FILE *arquivo;
    Veiculo veiculo;
    
    arquivo = fopen("veiculos.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    do {
        printf("Digite o ID do veiculo: ");
        scanf("%d", &veiculo.id);
        getchar();
        
        if (!validarID(veiculo.id)) {
            printf("ID ja existe! Tente outro.\n");
        }
    } while (!validarID(veiculo.id));
    
    printf("Digite o modelo do veiculo: ");
    fgets(veiculo.modelo, 50, stdin);
    veiculo.modelo[strcspn(veiculo.modelo, "\n")] = 0;
    
    do {
        printf("Digite a placa do veiculo: ");
        fgets(veiculo.placa, 10, stdin);
        veiculo.placa[strcspn(veiculo.placa, "\n")] = 0;
        
        if (!validarPlaca(veiculo.placa)) {
            printf("Placa ja cadastrada! Tente outra.\n");
        }
    } while (!validarPlaca(veiculo.placa));
    
    printf("Digite o ano do veiculo: ");
    scanf("%d", &veiculo.ano);
    
    fprintf(arquivo, "%d,%s,%s,%d\n", veiculo.id, veiculo.modelo, veiculo.placa, veiculo.ano);
    fclose(arquivo);
    printf("Veiculo adicionado com sucesso!\n");
}

void alterarVeiculo() {
    FILE *arquivo, *temp;
    char linha[256];
    int id, encontrado = 0;
    Veiculo veiculo;
    int opcao;
    char placa_temp[10];
    
    printf("Digite o ID do veiculo a ser alterado: ");
    scanf("%d", &id);
    getchar();
    
    arquivo = fopen("veiculos.txt", "r");
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
            printf("1. Modelo\n2. Placa\n3. Ano\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);
            getchar();
            
            veiculo.id = id;
            strcpy(veiculo.modelo, strtok(NULL, ","));
            strcpy(veiculo.placa, strtok(NULL, ","));
            veiculo.ano = atoi(strtok(NULL, ","));
            
            switch(opcao) {
                case 1:
                    printf("Digite o novo modelo: ");
                    fgets(veiculo.modelo, 50, stdin);
                    veiculo.modelo[strcspn(veiculo.modelo, "\n")] = 0;
                    break;
                case 2:
                    do {
                        printf("Digite a nova placa: ");
                        fgets(placa_temp, 10, stdin);
                        placa_temp[strcspn(placa_temp, "\n")] = 0;
                        
                        if (!validarPlaca(placa_temp)) {
                            printf("Placa ja cadastrada! Tente outra.\n");
                        } else {
                            strcpy(veiculo.placa, placa_temp);
                            break;
                        }
                    } while (1);
                    break;
                case 3:
                    printf("Digite o novo ano: ");
                    scanf("%d", &veiculo.ano);
                    break;
                default:
                    printf("Opcao invalida!\n");
                    break;
            }
            fprintf(temp, "%d,%s,%s,%d\n", veiculo.id, veiculo.modelo, veiculo.placa, veiculo.ano);
        } else {
            fputs(linha, temp);
        }
    }
    
    fclose(arquivo);
    fclose(temp);
    
    if (encontrado) {
        remove("veiculos.txt");
        rename("temp.txt", "veiculos.txt");
        printf("Dados alterados com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Veiculo nao encontrado!\n");
    }
}

void excluirVeiculo() {
    FILE *arquivo, *temp;
    char linha[256];
    int id;
    int encontrado = 0;
    
    printf("Digite o ID do veiculo a ser excluido: ");
    scanf("%d", &id);
    
    arquivo = fopen("veiculos.txt", "r");
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
        remove("veiculos.txt");
        rename("temp.txt", "veiculos.txt");
        printf("Veiculo excluido com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Veiculo nao encontrado!\n");
    }
}

void consultarVeiculo() {
    FILE *arquivo;
    char linha[256], placa_busca[10];
    int encontrado = 0;
    char temp[256];
    
    printf("Digite a placa do veiculo: ");
    getchar();
    fgets(placa_busca, 10, stdin);
    placa_busca[strcspn(placa_busca, "\n")] = 0;
    
    arquivo = fopen("veiculos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    while (fgets(linha, 256, arquivo)) {
        strcpy(temp, linha);
        char *id = strtok(temp, ",");
        char *modelo = strtok(NULL, ",");
        char *placa = strtok(NULL, ",");
        char *ano = strtok(NULL, ",");
        
        if (strcmp(placa, placa_busca) == 0) {
            printf("\nInformacoes do Veiculo:\n");
            printf("ID: %s\n", id);
            printf("Modelo: %s\n", modelo);
            printf("Placa: %s\n", placa);
            printf("Ano: %s", ano);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("Veiculo nao encontrado!\n");
    }
    
    fclose(arquivo);
}

void listarVeiculos() {
    FILE *arquivo;
    char linha[256];
    
    arquivo = fopen("veiculos.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    printf("\nLista de Veiculos:\n");
    printf("ID | Modelo | Placa | Ano\n");
    printf("--------------------------------\n");
    
    while (fgets(linha, 256, arquivo)) {
        char *id = strtok(linha, ",");
        char *modelo = strtok(NULL, ",");
        char *placa = strtok(NULL, ",");
        char *ano = strtok(NULL, ",");
        
        if (id && modelo && placa && ano) {
            printf("%s | %s | %s | %s", id, modelo, placa, ano);
        }
    }
    
    fclose(arquivo);
}

int main() {
    int opcao;
    
    do {
        printf("\n=== Sistema de Registro de Veiculos ===\n");
        printf("1. Adicionar novo veiculo\n");
        printf("2. Alterar dados de um veiculo\n");
        printf("3. Excluir veiculo\n");
        printf("4. Consultar veiculo pela placa\n");
        printf("5. Listar todos os veiculos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                adicionarVeiculo();
                break;
            case 2:
                alterarVeiculo();
                break;
            case 3:
                excluirVeiculo();
                break;
            case 4:
                consultarVeiculo();
                break;
            case 5:
                listarVeiculos();
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
