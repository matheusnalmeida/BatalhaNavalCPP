#pragma once
#include "VetorDinamico.h"
#include "Barco.h"
class Tabuleiro {
private:
	VetorDinamico<VetorDinamico<char>*>* matriz;
	/*
	Ira armazenar:
	-D = Direita
	-E = Esquerda
	-C = Cima
	-B = Baixo
	*/
	VetorDinamico<char>* vetorDeDirecoes;
	/*
	Ira armazenar as posicoes livres:
	Exemplo[[1,2,3],[4,5,6],[9]]
	*/
	VetorDinamico<VetorDinamico<int>*>* posicoes_livres2d;
	VetorDinamico<int>* posicoes_livres1d;
	VetorDinamico<Barco*>* vetorDeBarcos;
	void gerarTabuleiroAleatorio();
	//Verifica se o intervalo de posicoes passado e valido
	bool validaIntervalo(int x, int y, int posicaoinicio, int posicaoFim, char posicao);
	//Ira verificar se as coordenadas passadas sao validas
	bool validaCoordenadas(int x, int y);
	//Ira verificar se as coordenadas passadas possuem barco
	bool verificaBarcoExiste(int x, int y);
	char escolherDirecao(VetorDinamico<char>* vetorDeDirecoes);
public:
	Tabuleiro();
	~Tabuleiro();
	bool cadastrarBarco(int x,int y,Barco* barco);
	void printarTabuleiro();
	//Retorna o valor que esta armazenado na posicao xy da matriz
	char valorLinhaColuna(int x, int y);
};