package model;

public class Revista extends ItemBiblioteca {
    private int numeroEdicao;
    private String mesPublicacao;
    
    public Revista(String titulo, String autor, int anoPublicacao, int numeroEdicao, String mesPublicacao) {
        super(titulo, autor, anoPublicacao);
        this.numeroEdicao = numeroEdicao;
        this.mesPublicacao = mesPublicacao;
    }
    
    public int getNumeroEdicao() {
        return numeroEdicao;
    }
    
    public void setNumeroEdicao(int numeroEdicao) {
        this.numeroEdicao = numeroEdicao;
    }
    
    public String getMesPublicacao() {
        return mesPublicacao;
    }
    
    public void setMesPublicacao(String mesPublicacao) {
        this.mesPublicacao = mesPublicacao;
    }
    
    @Override
    public void exibirDados() {
        System.out.println("REVISTA - Título: " + titulo + " | Autor: " + autor + 
                          " | Ano: " + anoPublicacao + " | Edição: " + numeroEdicao + 
                          " | Mês: " + mesPublicacao);
    }
}
