

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

    void enfileirar(int titulo, const string& nome) {
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

        cout << "Eleitor " << nome << " adicionado � fila." << endl;
    }

    void desenfileirar() {
        if (estaVazia()) {
            cout << "A fila est� vazia." << endl;
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
            cout << "A fila est� vazia." << endl;
            return;
        }

        Eleitor* atual = primeiro;
        cout << "Fila de eleitores:" << endl;
        while (atual != NULL) {
            cout << "T�tulo: " << atual->titulo << ", Nome: " << atual->nome << endl;
            atual = atual->proximo;
        }
    }
};
