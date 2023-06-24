#define FILAELEITOR_H

#include <iostream>
#include <string>
using namespace std;
struct Eleitor {
    int titulo;
    string nome;
    Eleitor* proximo;
};
class FilaEleitor {
private:
    Eleitor* primeiro;
    Eleitor* ultimo;

public:
    FilaEleitor() {
        primeiro = NULL;
        ultimo = NULL;
    }

    bool estaVazia() {
        return primeiro == NULL;
    }

    void enfileirar(int titulo, const string &nome) {
        Eleitor* novoEleitor = new Eleitor;
        novoEleitor->titulo = titulo;
        novoEleitor->nome = nome;
        novoEleitor->proximo = NULL;

        if (estaVazia()) {
            primeiro = novoEleitor;
            ultimo = novoEleitor;
        } else {
            ultimo->proximo = novoEleitor;
            ultimo = novoEleitor;
        }

        cout << "Eleitor " << nome << " adicionado à fila." << endl;
    }

    void desenfileirar() {
        if (estaVazia()) {
            cout << "A fila está vazia." << endl;
            return;
        }

        Eleitor* eleitorRemovido = primeiro;
        primeiro = primeiro->proximo;

        if (primeiro == NULL) {
            ultimo = NULL;
        }

        cout << "Eleitor " << eleitorRemovido->nome << " removido da fila." << endl;
        delete eleitorRemovido;
    }

    void exibirFila() {
        if (estaVazia()) {
            cout << "A fila está vazia." << endl;
            return;
        }

        Eleitor* atual = primeiro;
        cout << "Fila de eleitores:" << endl;
        while (atual != NULL) {
            cout << "Título: " << atual->titulo << ", Nome: " << atual->nome << endl;
            atual = atual->proximo;
        }
    }
    
	int votar() {
    if (estaVazia()) {
        cout << "A fila está vazia" << endl;
        return -1; // Ou qualquer outro valor indicando uma situação de erro
    }
    
    Eleitor* atual = primeiro;
    while (atual != NULL) {
        return atual->titulo;
        atual = atual->proximo;
    }

    return -1; // Se a execução chegar aqui, significa que não foi possível encontrar o título de eleitor
}
    ~FilaEleitor() {
    Eleitor* atual = primeiro;
    while (atual != NULL) {
        Eleitor* proximo = atual->proximo;
        delete atual;
        atual = proximo;
    }
}
};
