#include "Barco.h"

Barco::Barco()
{
}

Barco::Barco(std::string nome, int tamanho)
{
	this->nome = nome;
	this->tamanho = tamanho;
}

Barco::~Barco()
{
}

std::string Barco::getNome()
{
	return this->nome;
}

int Barco::getTamanho()
{
	return this->tamanho;
}
