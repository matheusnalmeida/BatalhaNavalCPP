#pragma once
#include<string>
#include <ostream>
#include <iostream>
template<typename T>
class VetorDinamico {
public:
	VetorDinamico();
	VetorDinamico(int tamanho);
	VetorDinamico(bool permite_duplicadodos);
	~VetorDinamico();
	bool add(T element);
	void add(int index, T elemento);
	bool insert(int index, T elemento);
	void clear();
	bool contains(T element);
	T get(int index);
	int indexOf(T elemento);
	bool isEmpty();
	int lastIndexOf(T elemento);
	T remove(int index);
	int size();
	T menorElemento();
	T maiorElemento();
	friend std::ostream& operator<<(std::ostream& out, VetorDinamico<T>& vetor) {
		if (vetor.quantidade_de_elementos == 0) {
			out << "[]";
			return out;
		}
		out << "[";
		for (int i = 0; i < vetor.quantidade_de_elementos; i++) {
			out << vetor.vetor[i];
			if (i != vetor.size() - 1) {
				out << ", ";
			}
		}
		out << "]";

		return out;
	}

private:
	bool permite_duplicados = true;
	T* vetor;
	int quantidade_de_elementos;
	int tamanho_do_vetor;
	void resize(int lenght);

};

template<typename T>
VetorDinamico<T>::VetorDinamico() {
	this->tamanho_do_vetor = 10;
	this->vetor = new T[this->tamanho_do_vetor];
	this->quantidade_de_elementos = 0;
}

template<typename T>
VetorDinamico<T>::VetorDinamico(int tamanho) {
	this->tamanho_do_vetor = tamanho;
	this->vetor = new T[this->tamanho_do_vetor];
	this->quantidade_de_elementos = 0;
}

template<typename T>
VetorDinamico<T>::VetorDinamico(bool permite_duplicados) {
	this->vetor = new T[10];
	this->tamanho_do_vetor = 10;
	this->quantidade_de_elementos = 0;
	this->permite_duplicados = permite_duplicados;
}

template<typename T>
VetorDinamico<T>::~VetorDinamico() {
	delete[] this->vetor;
}

template<typename T>
void VetorDinamico<T>::resize(int lenght) {
	if (this->quantidade_de_elementos == this->tamanho_do_vetor) {
		T* novo_vetor = new T[(this->tamanho_do_vetor + lenght)];
		for (int i = 0; i < this->tamanho_do_vetor; i++) {
			novo_vetor[i] = this->vetor[i];
		}
		this->tamanho_do_vetor = this->tamanho_do_vetor + lenght;
		delete[] this->vetor;
		this->vetor = novo_vetor;
	}
}

template<typename T>
bool VetorDinamico<T>::add(T elemento) {
	if (this->contains(elemento)) {
		if (this->permite_duplicados) {
			this->resize(5);
			this->vetor[this->quantidade_de_elementos++] = elemento;
			return true;
		}
		else {
			return false;
		}
	}
	this->resize(5);
	this->vetor[this->quantidade_de_elementos++] = elemento;
	return true;
}

template<typename T>
void VetorDinamico<T>::add(int index, T elemento) {
	this->resize(5);
	if (index < 0 || index > this->quantidade_de_elementos) {
		return;
	}
	if (this->contains(elemento)) {
		if (this->permite_duplicados) {
			for (int i = quantidade_de_elementos - 1; i >= index; i--) {
				this->vetor[i + 1] = this->vetor[i];
			}
			this->vetor[index] = elemento;
			this->quantidade_de_elementos++;
			return;
		}
		else {
			return;
		}
	}
	for (int i = quantidade_de_elementos - 1; i >= index; i--) {
		this->vetor[i + 1] = this->vetor[i];
	}
	this->vetor[index] = elemento;
	this->quantidade_de_elementos++;
}

template<typename T>
inline bool VetorDinamico<T>::insert(int index, T elemento)
{
	if (index < 0 || index >= this->quantidade_de_elementos) {
		return false;
	}

	this->vetor[index] = elemento;

	return true;
}

template<typename T>
bool VetorDinamico<T>::contains(T elemento) {
	for (int i = 0; i < this->quantidade_de_elementos; i++) {
		if (this->vetor[i] == elemento) {
			return true;
		}
	}
	return false;
}

template<typename T>
void VetorDinamico<T>::clear() {
	delete[] this->vetor;
	this->tamanho_do_vetor = 10;
	this->vetor = new T[this->tamanho_do_vetor];
	this->quantidade_de_elementos = 0;
}

template<typename T>
T VetorDinamico<T>::get(int index) {
	if (index < 0 || index >= this->quantidade_de_elementos) {
		return T();
	}

	return this->vetor[index];
}

template<typename T>
T VetorDinamico<T>::remove(int index) {
	if (index < 0 || index >= this->quantidade_de_elementos || this->quantidade_de_elementos == 0) {
		return T();
	}

	T elemento_removido = this->get(index);

	for (int i = index; i < this->tamanho_do_vetor - 1; i++) {
		this->vetor[i] = this->vetor[i + 1];
	}
	this->vetor[this->tamanho_do_vetor - 1] = T();
	this->quantidade_de_elementos--;

	return elemento_removido;
}

template<typename T>
int VetorDinamico<T>::lastIndexOf(T elemento) {
	for (int i = this->quantidade_de_elementos - 1; i >= 0; i--) {
		if (this->vetor[i] == elemento) {
			return i;
		}
	}
	return -1;
}

template<typename T>
int VetorDinamico<T>::indexOf(T elemento) {
	for (int i = 0; i < this->quantidade_de_elementos; i++) {
		if (this->vetor[i] == elemento) {
			return i;
		}
	}
	return -1;
}

template<typename T>
bool VetorDinamico<T>::isEmpty() {
	return this->quantidade_de_elementos == 0;
}

template<typename T>
int VetorDinamico<T>::size() {
	return this->quantidade_de_elementos;
}

template<typename T>
inline T VetorDinamico<T>::menorElemento()
{
	if (this->isEmpty()) {
		return T();
	}
	T menorElemento = this->get(0);
	for (int i = 1; i < this->size(); i++) {
		if (this->get(i) < menorElemento) {
			menorElemento = this->get(i);
		}
	}

	return menorElemento;
}

template<typename T>
inline T VetorDinamico<T>::maiorElemento()
{
	if (this->isEmpty()) {
		return T();
	}
	T maiorElemento = this->get(0);
	for (int i = 1; i < this->size(); i++) {
		if (this->get(i) > maiorElemento) {
			maiorElemento = this->get(i);
		}
	}

	return maiorElemento;
}
