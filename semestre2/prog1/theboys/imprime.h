#ifndef IMPRIME
#define IMPRIME

//imprime heroi que chega na base e espera
void i_chega_fica(struct heroi h, struct base b, int tempo);

//imprime heroi que chega na base e desiste
void i_chega_sai(struct heroi h, struct base b, int tempo);

//imrprime heroi esperando na base b, e o tam da fila
void i_espera(struct heroi h, struct base b, int tempo);

//imprime heroi que desiste de esperar base b
void i_desiste(struct heroi h, struct base b, int tempo);

//porteiro avisa herois para entrarem, e a fila de espera
void i_avisa(struct base b, int tempo);

//imprime os herois h que sao admitidos pelo porteiro na base b
void i_avisa_admite(int idheroi, struct base b, int tempo);

//imprime os herois h que entram na base b, tambem quando vao sair
void i_entra(struct heroi h, struct base b, int tempo, int sai);

//imprime os herois h que saem da base b, tambem a lotação apos a saida
void i_sai(struct heroi h, struct base b, int tempo);

//imprime a base de saida e de destino de heroi h em uma viagem, tambem quando chega, distancia e velocidade
void i_viaja(struct heroi h, int b_atual, int b_dest, int dis, int chega, int tempo);

//declara a morte de heroi h
void i_morre(int idheroi, int idmissao, int tempo);

//primeira mensagem exposta quando vai ocorrer uma missao mi
//mostra habilidades necessárias e tentativas
void i_missao(struct missao mi, int tempo);

//declara a missão mi como feita por b base, que tinham herois que formam o conjunto hab
//de habilidades tottais
void i_missao_feita(struct missao mi, int baseid, struct cjto_t *hab, int tempo);

//declara a missao mi como impossivel para fazer agora
void i_missao_impossivel(struct missao mi, int tempo);

//mostra a tentativa da base b de fazer a missao mi, tambem mostra os herois e a distancia
void i_missao_teste(struct missao mi, int baseid, int dis, struct cjto_t *herois,int tempo);

//mostra o herio h de certa base na tentativa de fazer a missao mi,e seu conjunto de habilidades
void i_missao_heroi(struct missao mi, struct heroi h, int tempo);

//mostra a uniao das habilidades dos herois da base b que esta vendo se consegue fazer
//a missao mi
void i_missao_hab_t(struct missao mi, int idbase, struct cjto_t *hab_t, int tempo);

//log do fim do mundo
//imprime os herois e suas estatistiscas:
//id, se estao mortos, paciencia, velocidade, xp, habilidades
//imprime as bases e suas estatisticas:
//id, lotação, fila maxima atingida e missoes que participou
//mostra tambem eventos tratados, missoes cumpridas,
//tentativas por missao(com min, max e media)
//taxa de mortalidade
void log_fim(struct mundo *m);

#endif