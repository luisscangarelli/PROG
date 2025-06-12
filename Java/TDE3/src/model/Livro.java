package model;

public class Livro extends ItemBiblioteca {
    private String editora;
    private int numeroPaginas;
    
    public Livro(String titulo, String autor, int anoPublicacao, String editora, int numeroPaginas) {
        super(titulo, autor, anoPublicacao);
        this.editora = editora;
        this.numeroPaginas = numeroPaginas;
    }
    
    public String getEditora() {
        return editora;
    }
    
    public void setEditora(String editora) {
        this.editora = editora;
    }
    
    public int getNumeroPaginas() {
        return numeroPaginas;
    }
    
    public void setNumeroPaginas(int numeroPaginas) {
        this.numeroPaginas = numeroPaginas;
    }
    
    @Override
    public void exibirDados() {
        System.out.println("LIVRO - Título: " + titulo + " | Autor: " + autor + 
                          " | Ano: " + anoPublicacao + " | Editora: " + editora + 
                          " | Páginas: " + numeroPaginas);
    }
}
