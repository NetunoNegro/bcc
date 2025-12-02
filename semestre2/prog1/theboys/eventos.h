#ifndef EVENTOS
#define EVENTOS

#define CHEGA 1
#define ESPERA 2
#define DESISTE 3
#define AVISA 4
#define ENTRA 5
#define SAI 6
#define VIAJA 7
#define MORRE 8
#define MISSAO 9
#define FIM 10

//quase todos os eventos, com excessão de insere_lef e executa_mundo
//chamam a função para imprimir no terminal o que acontece
//da biblioteca "imprime.h"

//struct especifica que representa quem participa do evento
//se só 1 elemento partiipa, vai estar no id1, e id2 sera -1
//se 2 elementos participão, sempre que tiver heroi vai ser id1, id2 é a outra informação
struct item_evento{
    int id1;
    int id2;
};

//insere elemento na lef do mundo
void insere_lef(struct mundo *m, int id1, int id2, int tipo, int tempo);

//heroi chega na base, insere na lef ou espera ou desiste
void chega(struct mundo *m, int idheroi, int idbase);

//heroi decide esperar na base, insere avisa na lef
void espera(struct mundo *m, int idheroi, int idbase);

//loop principal que percorre a lef do mundo
//vai ver qual é o proximo evento da lef e fazer ele
//pode ser qualquer um dessa biblioteca, como chega e espera, com excessão de:
//nao chama diretamente insere_lef
//nao chama eventos iniciais
void executa_mundo(struct mundo *m);

//heroi desiste de esperar na fila da base, insere viaja na lef
void desiste(struct mundo *m, int idheroi, int idbase);

//porteiro da base b "avisa", no caso atualiza a fila de espera da base
//entra os primeiros, quando tiver espaço na base
//insere entra na lef
void avisa(struct mundo *m, int idbase);

//heroi entra na base
//insere sai na lef (quando ele vai sair)
void entra(struct mundo *m, int idheroi, int idbase);

//heroi sai da base
//isere viaja na lef
//insere avisa na lef
void sai(struct mundo *m, int idheroi, int idbase);

//heroi viaja para alguma base aleatória
//insere chega na lef
void viaja(struct mundo *m, int idheroi, int idbase);

//setup dos eventos iniciais
//determina os momentos que os herois vao chegar nas bases
//determina os momentos que as missoes vão começar
void eventos_iniciais(struct mundo *m);

#endif