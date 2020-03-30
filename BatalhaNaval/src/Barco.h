#pragma once
#include <string>
#include <ostream>
#include "VetorDinamico.h"
class Barco {
private:
	int tamanho;
	std::string nome;
	//Vetor de posicoes ocupadas
	VetorDinamico<VetorDinamico<int>*>* vetor_de_posicoes;
public:
	Barco();
	Barco(std::string nome, int tamanho);
	~Barco();
	std::string getNome();
	int getTamanho();
	VetorDinamico<VetorDinamico<int>*>* getCoordenadas();
	void cadastrarPosicao(int x, int y);
	//Metodo a ser chamado quando o barco for atingido
	void reduzirTamanho();
	friend std::ostream& operator<<(std::ostream& out, Barco& barco) {
		out << barco.nome;
		return out;
	}
};