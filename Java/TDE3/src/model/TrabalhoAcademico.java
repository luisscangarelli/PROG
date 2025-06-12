package model;

public class TrabalhoAcademico extends ItemBiblioteca {
    private String instituicao;
    private String tipoTrabalho;
    
    public TrabalhoAcademico(String titulo, String autor, int anoPublicacao, String instituicao, String tipoTrabalho) {
        super(titulo, autor, anoPublicacao);
        this.instituicao = instituicao;
        this.tipoTrabalho = tipoTrabalho;
    }
    
    public String getInstituicao() {
        return instituicao;
    }
    
    public void setInstituicao(String instituicao) {
        this.instituicao = instituicao;
    }
    
    public String getTipoTrabalho() {
        return tipoTrabalho;
    }
    
    public void setTipoTrabalho(String tipoTrabalho) {
        this.tipoTrabalho = tipoTrabalho;
    }
    
    @Override
    public void exibirDados() {
        System.out.println("TRABALHO ACADÊMICO - Título: " + titulo + " | Autor: " + autor + 
                          " | Ano: " + anoPublicacao + " | Instituição: " + instituicao + 
                          " | Tipo: " + tipoTrabalho);
    }
}
