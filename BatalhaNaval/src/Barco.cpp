#include "Barco.h"

Barco::Barco()
{
}

Barco::Barco(std::string nome, int tamanho)
{
	this->nome = nome;
	this->tamanho = tamanho;
	this->vetor_de_posicoes = new VetorDinamico<VetorDinamico<int>*>();
}

Barco::~Barco()
{
	for (int i = 0; i < this->vetor_de_posicoes->size(); i++) {
		delete this->vetor_de_posicoes->get(i);
	}
	delete this->vetor_de_posicoes;
}

std::string Barco::getNome()
{
	return this->nome;
}

int Barco::getTamanho()
{
	return this->tamanho;
}

VetorDinamico<VetorDinamico<int>*>* Barco::getCoordenadas()
{
	return this->vetor_de_posicoes;
}

void Barco::cadastrarPosicao(int x, int y)
{
	if ((0 <= x && x < 10) || (0 <= y && y < 10)) {
		VetorDinamico<int>* vetor_novas_coordenadas = new VetorDinamico<int>(2);
		vetor_novas_coordenadas->add(x); vetor_novas_coordenadas->add(y);
		this->vetor_de_posicoes->add(vetor_novas_coordenadas);
	}
}

void Barco::reduzirTamanho()
{
	this->tamanho--;
}
