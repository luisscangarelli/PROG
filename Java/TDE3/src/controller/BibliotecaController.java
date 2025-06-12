package controller;

import model.*;
import java.util.ArrayList;
import java.util.Scanner;

public class BibliotecaController {
    private ArrayList<ItemBiblioteca> itens;
    private Scanner scanner;
    
    public BibliotecaController() {
        this.itens = new ArrayList<>();
        this.scanner = new Scanner(System.in);
    }
    
    public void adicionarItem(int tipoItem) throws CampoVazioException {
        System.out.print("Título: ");
        String titulo = scanner.nextLine();
        if (titulo.trim().isEmpty()) {
            throw new CampoVazioException("O título não pode estar vazio!");
        }
        
        System.out.print("Autor: ");
        String autor = scanner.nextLine();
        if (autor.trim().isEmpty()) {
            throw new CampoVazioException("O autor não pode estar vazio!");
        }
        
        System.out.print("Ano de Publicação: ");
        int anoPublicacao = scanner.nextInt();
        scanner.nextLine();
        
        switch (tipoItem) {
            case 1: // Livro
                System.out.print("Editora: ");
                String editora = scanner.nextLine();
                if (editora.trim().isEmpty()) {
                    throw new CampoVazioException("A editora não pode estar vazia!");
                }
                System.out.print("Número de Páginas: ");
                int numeroPaginas = scanner.nextInt();
                scanner.nextLine();
                
                itens.add(new Livro(titulo, autor, anoPublicacao, editora, numeroPaginas));
                System.out.println("Livro cadastrado com sucesso!");
                break;
                
            case 2: // Revista
                System.out.print("Número da Edição: ");
                int numeroEdicao = scanner.nextInt();
                scanner.nextLine();
                System.out.print("Mês de Publicação: ");
                String mesPublicacao = scanner.nextLine();
                if (mesPublicacao.trim().isEmpty()) {
                    throw new CampoVazioException("O mês de publicação não pode estar vazio!");
                }
                
                itens.add(new Revista(titulo, autor, anoPublicacao, numeroEdicao, mesPublicacao));
                System.out.println("Revista cadastrada com sucesso!");
                break;
                
            case 3: // Trabalho Acadêmico
                System.out.print("Instituição: ");
                String instituicao = scanner.nextLine();
                if (instituicao.trim().isEmpty()) {
                    throw new CampoVazioException("A instituição não pode estar vazia!");
                }
                System.out.print("Tipo de Trabalho (TCC, Dissertação, Tese): ");
                String tipoTrabalho = scanner.nextLine();
                if (tipoTrabalho.trim().isEmpty()) {
                    throw new CampoVazioException("O tipo de trabalho não pode estar vazio!");
                }
                
                itens.add(new TrabalhoAcademico(titulo, autor, anoPublicacao, instituicao, tipoTrabalho));
                System.out.println("Trabalho Acadêmico cadastrado com sucesso!");
                break;
        }
    }
    
    public void listarItens() {
        if (itens.isEmpty()) {
            System.out.println("Nenhum item cadastrado na biblioteca.");
            return;
        }
        
        System.out.println("\n=== ITENS CADASTRADOS NA BIBLIOTECA ===");
        for (ItemBiblioteca item : itens) {
            item.exibirDados();
        }
    }
    
    public void buscarItemPorTitulo() throws ItemNaoEncontradoException {
        System.out.print("Digite o título para busca: ");
        String tituloBusca = scanner.nextLine();
        
        boolean encontrado = false;
        System.out.println("\n=== RESULTADOS DA BUSCA ===");
        
        for (ItemBiblioteca item : itens) {
            if (item.getTitulo().toLowerCase().contains(tituloBusca.toLowerCase())) {
                item.exibirDados();
                encontrado = true;
            }
        }
        
        if (!encontrado) {
            throw new ItemNaoEncontradoException("Nenhum item encontrado com o título: " + tituloBusca);
        }
    }
    
    public void removerItem() throws ItemNaoEncontradoException {
        System.out.print("Digite o título do item a ser removido: ");
        String tituloRemover = scanner.nextLine();
        
        ItemBiblioteca itemRemover = null;
        for (ItemBiblioteca item : itens) {
            if (item.getTitulo().equalsIgnoreCase(tituloRemover)) {
                itemRemover = item;
                break;
            }
        }
        
        if (itemRemover != null) {
            itens.remove(itemRemover);
            System.out.println("Item removido com sucesso!");
        } else {
            throw new ItemNaoEncontradoException("Item não encontrado: " + tituloRemover);
        }
    }
    
    public int getTotalItens() {
        return itens.size();
    }
}
