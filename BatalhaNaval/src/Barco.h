#pragma once
#include <string>
#include <ostream>
class Barco {
private:
	int tamanho;
	std::string nome;
public:
	Barco();
	Barco(std::string nome, int tamanho);
	~Barco();
	std::string getNome();
	int getTamanho();
	friend std::ostream& operator<<(std::ostream& out, Barco& barco) {
		out << barco.nome;
		return out;
	}
};