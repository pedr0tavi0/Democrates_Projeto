#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include "FilaEleitor.h"

using namespace std;

struct Candidato{
	int numero;
	string nome;
	Candidato *proximo;
};

struct Voto{
	int titulo;
	string nome;
	Voto *proximo;
};

//função para salvar os candidatos no arquivo txt
void salvarCandidatoNotxt(const Candidato* candidato) {  
	//verificando a existencia do arquivo Candidatos.txt
    ofstream arquivo("Candidatos.txt", ios::app);
    //abre o arquivo
    if (arquivo.is_open()) {
    	// fazendo o salvamento das variaveis nos parametros do arquivo
        arquivo << candidato->nome << ", " << candidato->numero << endl;
        //fechando arquivo
        arquivo.close();
        cout << "Candidato salvo com sucesso no arquivo Candidatos.txt" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo Candidatos.txt" << endl;
    }
}

// função do sub menu do candidato
int menuCandidatos(){
	cout << "---Area do candidato---"<<endl;
	cout << "------Bem Vindo!!-----" << endl;
	cout << "Escolha uma opção" << endl;
	cout << "[1] - Inserir um novo candidato" << endl;
	cout << "[2] - Lista dos candidatos já cadastrados" << endl;
	cout << "[3] - Remover um candidato" << endl;
	cout << "[4] - Voltar" << endl;
	int subopc; //variavel instanciadda para salvar a opção escolida
	cin >> subopc;
	return subopc;
}

void insereCandidato(Candidato*& lista, const std::string& nome, int numero) { //função que insere o new candidato na lista encadeada
    //instanciando as variaveis do no do new candiddato na lista encadeada
	Candidato* newCandidato = new Candidato;
    newCandidato->nome = nome;
    newCandidato->numero = numero;
    newCandidato->proximo = NULL;

    if (lista == NULL) { // caso a lista esteja vazia o candidato inserido ficara na primeira posição
        lista = newCandidato;
        salvarCandidatoNotxt(newCandidato); //chamando a função  para salvar o new candidato no txt
    } else {
        Candidato* ultimo = lista; // se a lista ja tiver sido populada o ponteiro candidato será percorrido até a ultima posição
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo; // quando o ultimo ofr diferente de nullo o ponteiro apontara para o ultimo candidato da lista
        }
        ultimo->proximo = newCandidato;//o ponteiro da ultima posição ira apontar para o new candidato salvando ele na ultima posição
        salvarCandidatoNotxt(newCandidato); // e salvando no arquivo txt
    }
}
void cadastroCandidato(Candidato* lista){ //função para a passagens de parametros do nome e numero do candidato para entrar na lista
	string nome;
	int num;
	cout << "Insira o nome do Candidato: ";
	cin >> nome;
	cout << "Insira o numero do candidato: ";
	cin >> num;
	insereCandidato(lista, nome, num);
	 
}
void percorreCandidatos(Candidato*& lista) {     //função para percorrer o arquivo txt e passar as informçãoes para a lista encadeada
    ifstream arquivo("Candidatos.txt"); //verifica se existe o arquivo
    if (arquivo.is_open()) {//verifica se o arquivo esta aberto
        string nome;
        int numero;
        while (arquivo >> nome >> numero) { // percorre o arquivo txt pelas colunas nome e numero
            Candidato* newCandidato = new Candidato; //declarando a variavel candidato do tipo no para salvar as informações dos candidatos 
            newCandidato->nome = nome;               // que foi obtido pelo percorrido do txt
            newCandidato->numero = numero;
            newCandidato->proximo = NULL;

            if (lista == NULL) {   //verifica se a lista esta vazia
                lista = newCandidato;  // insere um novo candidato na lista 
            } else {
                Candidato* atual = lista; // se a lista estiver populada um ponteiro sera criado para percorrer a lista
                while (atual->proximo != NULL) {
                    atual = atual->proximo;
                }                              //assim fazendo o ponteiro percorrido apontar para o ultimo nó da lista 
                atual->proximo = newCandidato;  // onde será no ultimo lugar da lista inserido o novo candidato
            }
        }
        arquivo.close();
        cout << "Candidatos carregados com sucesso!" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo." << endl;
    }
    
    
}
void listarCandidatos(const Candidato* lista) { //função para listar os candidatos
    if (lista == NULL) {
        cout << "Nenhum candidato foi cadastrado!." << endl; //mensagem de error caso não temha ninguem na lista
        return;
    }
    
    const Candidato* candidatoAtual = lista;  //instanciado uma variavel do tipo no que percorrera a lista pelos nó traznedo as informações dos candidatos
    while (candidatoAtual != NULL) {
        cout << "Nome: " << candidatoAtual->nome << " Número: " << candidatoAtual->numero << endl;
        candidatoAtual = candidatoAtual->proximo;
    }
}

//função para sobreescrever o arquivo quando um candidato for tirado da lista atraves de um ponteiro que percorrera a lista 
void sobrescreveArquivo(Candidato *&lista){
	 ofstream arquivo("Candidatos.txt");
    if (arquivo.is_open()) {
        Candidato *atual = lista;
        while (atual != NULL) {
            arquivo << atual->nome << ", " << atual->numero << endl; // assim sobreescrevendo o candidato excluido 
            atual = atual->proximo;
        }
        arquivo.close();
    } else {
        cout << "Erro ao sobrescrever o arquivo" << endl;
    }
}
//função que liberara a memoria da lista de candidatos para não ter lixo de memoria
void liberarMemoriaC(Candidato *&lista){
	Candidato *candidatoAtual = NULL;
	if(lista == NULL){
		cout << "";
             //caso a lista não estiver vazia o ponteiro do tipo no percorerra a lista
		     //e ele ira receber a posição seguinte do candidato atual que sera tirado da memoria
	}else{
		candidatoAtual = lista;
		while(candidatoAtual != NULL){
			Candidato *prox = candidatoAtual->proximo;
			delete candidatoAtual;
			//assim apos deletado  a variavel recebera o valor do ponteiro prox que a ponta o valor do proximo candidato em sequencia
			candidatoAtual = prox;
		}
		lista = NULL;
	}
}

//função para remover o candidato está com problemas para funcionar
void removeCandidato(Candidato *&lista) {
	
    percorreCandidatos(lista);//percorrendo os candidatos que esão no arquivo

    if (lista == NULL) {
        cout << "Nenhum candidato cadastrado até o momento" << endl;
    } else {
    	listarCandidatos(lista); // mpostrando os candidatos para a escolha de qual será removido
        int num = 0;
        cout << "Informe o número do candidato que deseja excluir: ";
        cin >> num;

        Candidato *auxiliar = NULL;
        Candidato *atual = lista;
        
           // duas variaveis do tipo no que percorreram a lista , o auxiliar para guardar na memoria a lista antes da exclusao
           // e o outro para percorrer a lista dos candidtaos agora

        while (atual != NULL) { //faznedo a verificaçãoo do num que foi passado e o numero do candidato que esta na lista
            if (num == atual->numero) {
                if (auxiliar == NULL) { // passando o valor do proximo candidato da sequencia para a lista pois o atual será excluido  "fazendo a dança das cadeiras"
              		   		 	 	   	// assim movendo o ponteiro para o candidato subsequente
                    lista = atual->proximo;
                } else {
                	//se nao a variavel auxiliar->proximo recebera o proximo elemtio da lista
                    auxiliar->proximo = atual->proximo;
                }
                //tirando  o candidato que foi passsado pelos parametros
                delete atual;
                cout << "Candidato removido com sucesso" << endl;
                break;
            } else {
            	
            	//caso não seja o valor selecionado o ponteiro auxiliar recebera o valor do candidato atual
                auxiliar = atual;
                //e o ponteiro autual ira apontar para o proximo candidato da lista
                atual = atual->proximo;
            }
        }
        sobrescreveArquivo(lista);//sobreescrevendo os arquivos depois de deletado o candidato
    }

    liberarMemoriaC(lista);//liberando memoria da lista dinamica de candidatos.
}

//função para exibir as opções do eleitor
int menuEleitores(){
	cout << "----Area do Eleitor----"<<endl;
	cout << "------Bem Vindo!!-----" << endl;
	cout << "Escolha uma opção" << endl;
	cout << "[1] - Insira um novo eleitor" << endl;
	cout << "[2] - Listar eleitores cadastrados" << endl;
	cout << "[3] - Voltar" << endl;
	int subopc; //variavel para salvar na memoria qual opção foi escolhida
	cin >> subopc;
	return subopc;
}
//função para salvar os eleitores no arquivo txt
void salvarEleitorNotxt(Eleitor *eleitor){
	ofstream arquivo("Eleitores.txt", ios::app);//verificar se a o arquivo
    if (arquivo.is_open()) {//abrira o arquivo
        arquivo << eleitor->nome << ", " << eleitor->titulo << endl;//inserindo as informaçoes nas colunas em sequencia
        arquivo.close();
        cout << "Candidato salvo com sucesso no arquivo Eleitores.txt" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo Eleitores.txt" << endl;
    }
}

//funação que inserirá o eleitor na lista encadeada
void inserirEleitor(Eleitor*& lista, const std::string& nome, int numero){
	Eleitor* newEleitor = new Eleitor;
    newEleitor->nome = nome;
    newEleitor->titulo = numero;
    newEleitor->proximo = NULL;

    if (lista == NULL) { //se a lista etiver vazia ira colocar na primeira posição
        lista = newEleitor;
        salvarEleitorNotxt(newEleitor);
    } else { //se nao a lista ira percorrer atraves do ponteiro e será salvo na ultima posição da lista
        Eleitor* ultimo = lista;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = newEleitor;
        salvarEleitorNotxt(newEleitor);// salvando o new eleitor no arquivo txt
    }
}

//função para cadastrar o eleitor atrves dos parametros fornecidos
void cadastraEleitor(Eleitor *lista){
	string nome;
	int num;
	cout << "Insira o nome do Eleitor: ";
	cin >> nome;
	cout << "Insira o numero do titulo de eleitor: ";
	cin >> num;
	inserirEleitor(lista, nome, num); //chamando a função e fazendo as passagens de parametros para a lista encadeada
}
//função para percorrer o arquivo txt de eleitores e salvar as informações, passando para lista encadeada
void percorrerEleitores(Eleitor *&lista) {
    ifstream arquivo("Eleitores.txt");
    if (arquivo.is_open()) {
        string nome;
        int numero;
        while (arquivo >> nome >> numero) { // percorre o arquivo txt pelas colunas nome e numero
            Eleitor* newEleitor = new Eleitor; //declarando a variavel eleitor do tipo no para salvar as informações dos candidatos 
            newEleitor->nome = nome;
            newEleitor->titulo = numero;
            newEleitor->proximo = NULL;

            if (lista == NULL) {
                lista = newEleitor;
            } else { //caso a lista estiver populada percorrera um ponteiro até o ultimo lugar da lista 
                Eleitor* atual = lista; 
                while (atual->proximo != NULL) { //assim fazendo-o apontar para o ultimo no da lista onde la sera inserido no new eleitor
                    atual = atual->proximo;
                }
                atual->proximo = newEleitor;
            }
        }
        arquivo.close();
        cout << "Eleitores carregados com sucesso!" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo!." << endl;
    }
    
    
}

//função para verificar se o eleitor esta ou não apto a votar
bool verificaApto(int titulo, Eleitor* lista) {
    Eleitor* eleitorAtual = lista;
    bool boolean = false;
    
    if (lista == NULL) {
        cout << "Não há eleitor a ser exibido" << endl;
        return false;
    } else {
        while (eleitorAtual != NULL) {
            if (eleitorAtual->titulo == titulo) { //verifica se o titulo digitado esta na lista que foi recebida pela variavel eleitor atual
                boolean = true;
                break;
            }
            eleitorAtual = eleitorAtual->proximo; //variavel para controle passsando para o proximo ponteiro da lista
        }
        return boolean;
    }
}
//função para liberar a memoria da lista dinamica de eleitores
void liberarMemoriaE(Eleitor *&lista){
	Eleitor *eleitorAtual = NULL;
	if(lista == NULL){
		cout << "";
		
		
	}else{
		eleitorAtual = lista;
		while(eleitorAtual != NULL){
			Eleitor *prox = eleitorAtual->proximo;
			delete eleitorAtual;
			eleitorAtual = prox;
		}
		lista = NULL;
	}
}
void listarEleitores(const Eleitor* lista) {
    if (lista == NULL) {
        cout << "Nenhum candidato cadastrado." << endl;
        return;
    }
    
    const Eleitor* eleitorAtual = lista;
    while (eleitorAtual != NULL) {
        cout << "Nome: " << eleitorAtual->nome << " Número: " << eleitorAtual->titulo << endl;
        eleitorAtual = eleitorAtual->proximo;
    }
}


int menu(){
	
	cout << "-----Menu------ " << endl;
	cout << "Escolha uma opção"<<endl;
	cout << "[1] - Area do Candidato" << endl;
	cout << "[2] - Area do Eleitor" << endl;
	cout << "[3] - Votação" << endl;
	cout << "[4] - Exibição dos votos"<<endl;
	cout << "[5] - Encerrar" << endl;
	int opc;
	cin >> opc;
	return opc;
}

//função para inserir elitores na fila de eleição

void insereFila(FilaEleitor*& fila, Eleitor *lista){
	int titulo;
	
	cout << "Entre na fila de votação!" << endl;
	cout << "Insira o numero de seu título de eleitor: ";
	cin >> titulo;
	
	if(verificaApto(titulo, lista)){ //chamando a função de verificação de apto a votar
		
		cout << "Voce esta apto a votar!!, entrando na fila de votação ..." << endl;
		Eleitor *eleitorAtual = lista;//passando a lista a variavel
		while(eleitorAtual != NULL){//perccorendo a lista de eleitores
			if(eleitorAtual->titulo == titulo){//verificando se o numero do titulo informado é o mesmo do titulo->eleitor atual
				fila->enfileirar(titulo, eleitorAtual->nome);//chamando a função/metodo que ira inserir na fila
				fila->exibirFila();//metodo/função que exibe a fila
			}
			eleitorAtual = eleitorAtual->proximo;// se não apontara para o proximo eleitor da fila
		}
		
		
	}else{
		cout << "Você não está Apto para votar!" << endl;
	}
	
}
//função para pesquisar o nome do candidato e exibilo
string pesquisaNomeCandidato(int num, Candidato *lista){
	Candidato *atual = lista;
	while(atual != NULL){
		if(num == atual->numero){
			string nome = atual->nome;
			return nome;
		}
		atual = atual->proximo;
	}
	return "";
}

//função para inserir o voto na lista 
void inserirVoto(Voto*& lista, const std::string& nome, int numero){
	Voto* newVoto = new Voto; //declarando o no voto com os parametros do new voto
    newVoto->nome = nome;
    newVoto->titulo = numero;
    newVoto->proximo = NULL;

    if (lista == NULL) {
        lista = newVoto;
        
    } else { //caso a lista ja esteja populada a variavel ira percorrer a lista e achara a ultima posição e ira colocar o new voto nela
        Voto* ultimo = lista;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = newVoto;
        
    }
}
//função para registrar o voto na lista
void votar(FilaEleitor*& fila,Voto*& votos,Candidato*& candidatos){
	int num;
	if(fila->estaVazia()){
		cout << "Não há eleitores na fila de eleição!" << endl;
		
	}else{
		int titulo = fila->votar();
		Candidato *atual = candidatos;
		listarCandidatos(candidatos);
		
		cout << "Insira o número do candidato que deseja votar: ";
		cin >> num;
		string nome = pesquisaNomeCandidato(num, candidatos);//chamando a função para marcar o candidato na lista de votos realizados
		if(nome != ""){
                
		inserirVoto(votos,nome,num );//chamando a função para iserir o voto na lista encadeada
		cout << "Voto concluido!" << endl;
        }else{
              cout << "Erro" << endl;
              } 
		
		fila->desenfileirar();//metodo/função para tirar o primeiro eleitor da lista apor votar
	}
}


int menuVoto(){
	int opc;
	cout << "------------Votação----------" << endl;
   	cout << "                              "<<endl;
	cout << "[1] - Cadastrar na votacao" << endl;
	cout << "[2] - Votar" << endl;
	cout << "[3] - Retornar" << endl;
	cin >> opc;
	return opc;
}

//função para salvaer em arquivo txt os votos por candidato
void salvarVotosCEmtxt(string nome, int qtd){
	ofstream arquivo("votos.txt", ios::app);
    if (arquivo.is_open()) {
    	arquivo << "Lista de Votos por candidatos: " << endl;
        arquivo << "Nome: " << nome << ", " <<"Quantidade de votos: "<< qtd << endl;
        arquivo.close();
        cout << "Candidato salvo com sucesso no arquivo Votos.txt" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo Votos.txt" << endl;
    }
}
//cfunção para salvar a quantidade de votos total
void salvarVotosQtdVotos(int qtd){
	ofstream arquivo("votos.txt", ios::app);
    if (arquivo.is_open()) {
    	arquivo << "Lista da quantidade de votos: " << endl;
        arquivo <<"Quantidade de votos: "<< qtd << endl;
        arquivo.close();
        cout << "Voto salvo com sucesso no arquivo Votos.txt" << endl;
    } else {
        cout << "Não foi possível abrir o arquivo Votos.txt" << endl;
    }
}
//função para salvaar a quantidade de votos por candidato
void listaQtdVotosCandidato(Voto*& votos, Candidato*& lista) {
    Candidato* candidatoAtual = lista;
    Voto* votoAtual = votos;

    if (votos == NULL) {
        cout << "As eleições ainda não foram realizadas!" << endl;
    } else {
        while (votoAtual != NULL) 
            votoAtual = votoAtual->proximo;
        }

        while (candidatoAtual != NULL) {
            int qtd = 0;
            votoAtual = votos;

            while (votoAtual != NULL) {
                if (candidatoAtual->nome == votoAtual->nome) {
                    qtd++;
                }
                votoAtual = votoAtual->proximo;
            }

            salvarVotosCEmtxt(candidatoAtual->nome, qtd);
            cout << "A quantidade de votos do candidato " << candidatoAtual->nome << " é: " << qtd << " votos" << endl;

            candidatoAtual = candidatoAtual->proximo;
        }
        
    }
}

//função para listar a quantidade de votos
void listaQtdVotos(Voto*& votos) {
    
    Voto* votoAtual = votos;

    if (votos == NULL) {
        cout << "As eleições ainda não foram realizadas!" << endl;
    } else {
        while (votoAtual != NULL) {
            cout << votoAtual->titulo << endl;
            votoAtual = votoAtual->proximo;
        }

        
		int qtd = 0;
        while (votoAtual != NULL) {
            
            qtd++;
            
            votoAtual = votoAtual->proximo;
            
        }
        cout << "A quantidade de votos é de: " << qtd << "votos" << endl;
        salvarVotosQtdVotos(qtd);
    }
    
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	FilaEleitor *fila = new FilaEleitor();
	
	int opc = menu();
	Candidato *listacandidatos = NULL;
	Eleitor *listaeleitores = NULL;
	Voto *listavotos = NULL;
	
	while(opc !=5){
		int subopc;
		if(opc == 1){
			subopc = menuCandidatos();
			while(subopc !=4){
				if(subopc == 1){
					cadastroCandidato(listacandidatos);
					liberarMemoriaC(listacandidatos);
				}else if(subopc == 2){
					percorreCandidatos(listacandidatos);
					listarCandidatos(listacandidatos);
					liberarMemoriaC(listacandidatos);
					
				}else if(subopc == 3){
					removeCandidato(listacandidatos);
				}else{
					cout << "Informe uma opção válida!" << endl;
				}
				subopc = menuCandidatos();
			}
		}else if(opc == 2){
			subopc = menuEleitores();
			while(subopc !=3){
				if(subopc == 1){
					
					cadastraEleitor(listaeleitores);
					liberarMemoriaE(listaeleitores);
				}else if(subopc == 2){
					percorrerEleitores(listaeleitores);
					listarEleitores(listaeleitores);
					liberarMemoriaE(listaeleitores);
				}
				subopc = menuEleitores();
			}
		}else if(opc == 3){
			subopc = menuVoto();
			while(subopc != 3){
				if(subopc == 1 ){
					
					percorrerEleitores(listaeleitores);
					insereFila(fila, listaeleitores);
					liberarMemoriaE(listaeleitores);
				}else if(subopc == 2){
					percorreCandidatos(listacandidatos);
					votar(fila, listavotos, listacandidatos);
					liberarMemoriaC(listacandidatos);
				}
				subopc = menuVoto();
			}
			
		}else if(opc == 4){
		     percorreCandidatos(listacandidatos);
			listaQtdVotosCandidato(listavotos,listacandidatos);
			listaQtdVotos(listavotos);
			liberarMemoriaC(listacandidatos);
		}else{
			cout << "Opção inválida"<<endl;
		}
		opc = menu();
	}
	delete fila;
}


