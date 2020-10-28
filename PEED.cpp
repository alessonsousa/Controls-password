

#include <iostream>
#include <stdlib.h>

using namespace std;

struct Senha{
	int id;
	int senha;
	int prioridade;  // 0 - normal | 1 - prioridade
	Senha *next;
};

struct SenhasChamadas{
	Senha* senha;
	SenhasChamadas *next;
};

struct senhasCanceladas{
	Senha* senha;
	senhasCanceladas *next;
};

Senha* inicializaSenha(){
	return NULL;
}

SenhasChamadas* inicializaSenhasChamadas(){
	return NULL;
}

/*
	paramentros:
	pontiero para a senha
	quantidade de senhas normais chamadas
	quantidade de senhas prioridades chamadas
	se é prioridade ou não
*/
void gerarSenha(Senha **senha, int qtdNormal, int qtdPrioridade, int prioridade = 0){
	Senha* s = (Senha*) malloc(sizeof(Senha));
	s->id =  (qtdNormal + qtdPrioridade)+1;
	s->prioridade = prioridade;
	if(prioridade){
		s->senha = ++qtdPrioridade;
	}else{
		s->senha = ++qtdNormal;
	}
	s->next = NULL;
	cout << "SENHA: " << (s->prioridade ? " P" : " N") << s->senha << "\nTIPO: " << (s->prioridade ? " PRIORITARIA" : " NORMAL") <<endl;
	if(*senha == NULL){
		*senha = s;
	}else{
		Senha* aux = *senha;
		while(aux->next != NULL){
			aux = aux->next;
		}
		aux->next = s;
	}
}

Senha* prioridade(Senha *senhas){
	Senha* s = senhas;
	while (s != NULL) {
		if (s->prioridade == 1) break;
		s = s->next;
	}
	if (s == NULL) return NULL;
	return s;
}

Senha* excluirsenha(Senha *senhas, int id){
	Senha* ant = NULL;
	Senha* s = senhas;

	while (s != NULL && s->id != id) {
		ant = s;
		s = s->next;
	}
	if(s == NULL){
		return senhas;
	}
	if (ant == NULL) {
		senhas = s->next;
	}else {
		ant->next = s->next;
	}
	free(s);
	return senhas;
}

void chamar(Senha** senhas, SenhasChamadas** senhasChamadas, int *cp){

	if(*senhas == NULL) return;

	Senha* s;
	if(*cp == 2){
		s = *senhas;
		*cp = 0;
	}else{
		Senha* prioridades = prioridade(*senhas);
		if(prioridades != NULL){
			s = prioridades;
			*cp = *cp + 1;
		}else{
			s = *senhas;
		}
	}

	if(s == NULL) return;

	SenhasChamadas* sc = (SenhasChamadas*) malloc(sizeof(SenhasChamadas));
	Senha *ant = (Senha*) malloc(sizeof(Senha));
	ant->id = s->id;
	ant->prioridade = s->prioridade;
	ant->senha = s->senha;
	ant->next = NULL;
	sc->senha = ant;
	sc->next = *senhasChamadas;
	*senhasChamadas = sc;
	cout << "SENHA CHAMADA: " << (s->prioridade ? " P" : " N") << s->senha << "\nTIPO: " << (s->prioridade ? " PRIORITARIA" : " NORMAL") << endl;
	*senhas = excluirsenha(*senhas, s->id);
}

void listarSenhas(Senha *senhas){
    cout << "\n---- SENHAS EM ESPERA ----\n";
    Senha* s;
    char aux;
    cout << "SENHA |  TIPO " << endl;
	for (s = senhas; s != NULL; s = s->next)

		cout << "  " << (s->prioridade ? " P" : " N") << s->senha  << "   | " << (s->prioridade ? " PRIORITARIA" : " NORMAL") << endl;
}

void listarSenhasChamadas(SenhasChamadas *senhasChamadas){
    cout << "\n---- SENHAS CHAMADAS ----\n";
    SenhasChamadas* s;
    cout << "ID | SENHA | TIPO " << endl;
	for (s = senhasChamadas; s != NULL; s = s->next)
		cout << " "   << (s->senha)->id << " |   " << ((s->senha)->prioridade ? " P" : " N")  << (s->senha)->senha << "   | " << ((s->senha)->prioridade ? " PRIORITARIA" : " NORMAL") << endl;
}


int main(void) {
	Senha* senhas = inicializaSenha();
	SenhasChamadas* senhasChamadas = inicializaSenhasChamadas();
	int cp = 2;
	int qtdPrioridade = 0;
	int qtdNormal = 0;
	int opcao;

	do{
		cout << "\n\n---- MENU PRINCIPAL ----\n\n";
	    cout << "1 - GERAR SENHA NORMAL\n";
	    cout << "2 - GERAR SENHA PRIORITARIA\n";
	    cout << "3 - CHAMAR A PROXIMA SENHA\n";
	    cout << "4 - LISTAR SENHAS EM ESPERA\n";
	    cout << "5 - LISTAR SENHAS CHAMADAS\n";
		cout << "6 - SAIR\n";
		cout << "DIGITE SUA OPCAO: ";
	    cin >> opcao;
		system("cls");

		switch(opcao){
			case 1: gerarSenha(&senhas, qtdNormal, qtdPrioridade);
				qtdNormal++;
				break;
			case 2: gerarSenha(&senhas, qtdNormal, qtdPrioridade, 1);
				qtdPrioridade++;
				break;
			case 3: chamar(&senhas, &senhasChamadas, &cp);
				break;
			case 4: listarSenhas(senhas);
				break;
			case 5: listarSenhasChamadas(senhasChamadas);
				break;
		}
	}while(opcao != 6);

	return 0;
}





















