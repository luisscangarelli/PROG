package view;

import controller.BibliotecaController;
import model.CampoVazioException;
import model.ItemNaoEncontradoException;
import java.util.Scanner;

public class Principal {
    public static void main(String[] args) {
        BibliotecaController controller = new BibliotecaController();
        Scanner scanner = new Scanner(System.in);
        int opcao;
        
        System.out.println("=== SISTEMA DE GERENCIAMENTO DE BIBLIOTECA ===");
        System.out.println("Bem-vindo ao sistema!");
        
        do {
            exibirMenu();
            opcao = scanner.nextInt();
            scanner.nextLine();
            
            try {
                switch (opcao) {
                    case 1:
                        System.out.println("\n--- CADASTRAR ITEM ---");
                        System.out.println("Tipo de item:");
                        System.out.println("1 - Livro");
                        System.out.println("2 - Revista");
                        System.out.println("3 - Trabalho Acadêmico");
                        System.out.print("Escolha: ");
                        int tipoItem = scanner.nextInt();
                        scanner.nextLine();
                        
                        if (tipoItem >= 1 && tipoItem <= 3) {
                            controller.adicionarItem(tipoItem);
                        } else {
                            System.out.println("Tipo de item inválido!");
                        }
                        break;
                        
                    case 2:
                        System.out.println("\n--- LISTAR ITENS ---");
                        controller.listarItens();
                        break;
                        
                    case 3:
                        System.out.println("\n--- BUSCAR ITEM ---");
                        controller.buscarItemPorTitulo();
                        break;
                        
                    case 4:
                        System.out.println("\n--- REMOVER ITEM ---");
                        controller.removerItem();
                        break;
                        
                    case 5:
                        System.out.println("\nTotal de itens cadastrados: " + controller.getTotalItens());
                        System.out.println("Obrigado por usar o Sistema de Biblioteca!");
                        System.out.println("Saindo...");
                        break;
                        
                    default:
                        System.out.println("Opção inválida! Tente novamente.");
                }
            } catch (CampoVazioException e) {
                System.out.println("ERRO: " + e.getMessage());
            } catch (ItemNaoEncontradoException e) {
                System.out.println("ERRO: " + e.getMessage());
            } catch (Exception e) {
                System.out.println("ERRO INESPERADO: " + e.getMessage());
            }
            
            if (opcao != 5) {
                System.out.println("\nPressione ENTER para continuar...");
                scanner.nextLine();
            }
            
        } while (opcao != 5);
        
        scanner.close();
    }
    
    private static void exibirMenu() {
        System.out.println("\n" + "=".repeat(50));
        System.out.println("           MENU PRINCIPAL");
        System.out.println("=".repeat(50));
        System.out.println("1 - Cadastrar item");
        System.out.println("2 - Listar todos os itens");
        System.out.println("3 - Buscar item por título");
        System.out.println("4 - Remover item");
        System.out.println("5 - Sair");
        System.out.println("=".repeat(50));
        System.out.print("Escolha uma opção: ");
    }
}
