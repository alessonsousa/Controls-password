/*
	https://www.ic.unicamp.br/~ra069320/PED/MC102/1s2008/Apostilas/Cap10.pdf
*/

#include <iostream>
#include <stdlib.h>

using namespace std; //usar o namespace STD para evitar simplicar o usos de comandos da stdlib que em sem isso fica std::cout e cin isso fica apenas o cout

struct Senha{ //strutura de senhas
	int id; // id da senha, serve para identicar a senha
	int senha; // a senha propriamente dita
	int prioridade;  // a prioridade que pode ser 0 - normal | 1 - prioridade
	Senha *next; // ponteiro para a proxima senha
};

struct SenhasChamadas{ //strutura para guardar as senhas j� chamadas
	Senha* senha; //ponteiro para a senha j� chamada
	SenhasChamadas *next; // pontiro para a proxima senha
};

struct senhasCanceladas{ //strutura para guardar senhas canceladas
	Senha* senha; //ponteiro para a senha cancelada
	senhasCanceladas *next; //pontiro para a proxima senha cancelada
};

//fun��o para inicializar a fila de senhas
Senha* inicializaSenha(){
	return NULL;
}

//fun��o para inicializar a fila de senhas chamamadas
SenhasChamadas* inicializaSenhasChamadas(){
	return NULL;
}

/*
fun��o para gerar as senhas
	paramentros:
	pontiero para a senha
	quantidade de senhas normais chamadas
	quantidade de senhas prioridades chamadas
	se � prioridade ou n�o
*/
void gerarSenha(Senha **senha, int qtdNormal, int qtdPrioridade, int prioridade = 0){
	Senha* s = (Senha*) malloc(sizeof(Senha)); //pontiero para guardar uma senha, alocando menemoria do tamano de uma strutura senha e convertendo para a senha
	s->id =  (qtdNormal + qtdPrioridade)+1; // atribuindo um id para a senha, ela � a soma de todas as senhas +1 pois a primeiro seria 0 caso n�o tivesse isso
	s->prioridade = prioridade; //atribuindo a prioridade a senha
	if(prioridade){ // caso tenha prioridade
		s->senha = ++qtdPrioridade; //a senha � o pr�ximo numero da sequencia de senhas prioritarias
	}else{ // se n�o
		s->senha = ++qtdNormal; // a senha � a pr�ximo n�mero da segu�ncia de senhas normais
	}
	s->next = NULL; // esse ponteiro deve apontar para o NULL pois ele deve ser adicionado em ultimo lugar na fila
	cout << "SENHA: " << (s->prioridade ? " P" : " N") << s->senha << "\nTIPO: " << (s->prioridade ? " PRIORITARIA" : " NORMAL") <<endl; //imprimi a senha a ser chamada
	if(*senha == NULL){ // se a fila for vazia
		*senha = s; // ele adiciona ela no inicio
	}else{ // se n�o
		Senha* aux = *senha; // cria um ponteiro auxiliar para senha
		while(aux->next != NULL){ // usamos um loop para percorrer todos realocando todos uma pocis�o a cima
			aux = aux->next;
		}// ao sair do looping pegaremos o ultimo lugar
		aux->next = s; //ent�o apontamos ele para a nova senha assim colocando ela no final da fila
	}
}

//fun��o para verificar se tem alguma senha com prioridade na fila
//	parementros
//	Senha* senhas, um ponteiro para uma fila de senhas
Senha* prioridade(Senha *senhas){
	Senha* s = senhas; // criamos um ponteiro para armazenar temporariamente a fila de senhas
	while (s != NULL) { // fazemos um loop at� chegar no fim da fila
		if (s->prioridade == 1) break; // caso encontre algum com prioridade ent�o quebre o looping
		s = s->next; //se n�o chame o proximo da fila
	}
	if (s == NULL) return NULL; // se a v�riavel s for NULL quer dizer que n�o tem prioridades na fila ou ela � vazia ent�o retornamos NULL
	return s; // se n�o retornamos a senha com prioridade encontrada
}

/*
fun��o para excluir a senha
paramentros
Senha* senha, ponteiro para a fila de senhas
int id, o id da senha a ser removido
*/
/*
   PARA FIGURAS DESSA FUN��O OLHAR A PAGINA 5 DO PDF QUE TEM NO INICIO DESTE DOCUMENTO

*/
Senha* excluirsenha(Senha *senhas, int id){
	Senha* ant = NULL; // criamos um ponteiro para a senha anterior
	Senha* s = senhas; // criams um ponteiro para percorrer a fila de senhas

	while (s != NULL && s->id != id) { // criamos um looping para percorrer as senhas at� o final da fila ou encontarar uma com o id que querermos
		ant = s; // salvamos o anterior
		s = s->next; // chamamos o proximo da fila que sera vailiado no loopning se ele � NULL ou contem o id que queromos
	}
	if(s == NULL){// se a senha for NULL quer dizer que chegamos at� o final e n�o achamos o item
		return senhas; // ent�o retornamos a fila de senha como ela est�
	}
	if (ant == NULL) { // se a senha anterior for NULL quer dizer que o que procuramos est� no topo da fila
		senhas = s->next; //ent�o removemos ela do topo alterando a priemira posi��o da fila para o proximo da fila
	}else { // se n�o quer dizer que o item que procuramos esta no meio da fila
		ant->next = s->next; // ent�o pedimos para que o anterior a posi��o que queremos remover pula o proximo da fila apontando para o proximo do proximo
	}
	free(s); // liberamos da memoria o ponteiro que criamos para percorrer as senhas
	return senhas; // retormanos a nova fila de senha
}

/*
fun��o para chamar as senhas
paramentros
Senha** senhas, pontieiro para um ponteiro de uma fila de senhas
SenhasChamadas** senhasChamadas, ponteiro para um ponteiro de fila de senhas que j� foram chamadas
int* cp, ponteiro para um contador de senhas prioritarias
*/
void chamar(Senha** senhas, SenhasChamadas** senhasChamadas, int *cp){

	if(*senhas == NULL) return; // se a fila de senhas for NULL ent�o a fila est� vazia e encerramos a fun��o

	Senha* s; // criamos um ponteiro para senhas
	if(*cp == 2){ // se j� foi chamada duas senhas priorit�rias
		s = *senhas; // ent�o chamar o proximo da fila, que sempre sera o primeiro
		*cp = 0; // zerar o contador de senhas priorit�rios chamadas
	}else{ // se n�o
		Senha* prioridades = prioridade(*senhas); // criamos um pontiro para senhas e inicializamos ele com a fun��o de prioridade que pode retornar NULL caso n�o tenha prioridade ou retornar um ponteiro para a senha que tenha prioridade
		if(prioridades != NULL){ // se n�o for NULL quer dizer que foi encontrado uma senha com prioridade
			s = prioridades; // ent�o atrinuimos ela ao ponteiro de senhas que criamos
			*cp = *cp + 1; // e incrementamos o contador de senha com prioridades chamadas
		}else{ // se n�o quer dizer que n�o foi encontrada senha com prioridade
			s = *senhas; // ent�o chamamos o proximo da fila, que sempre sera o primeiro
		}
	}

	SenhasChamadas* sc = (SenhasChamadas*) malloc(sizeof(SenhasChamadas)); // criamos um ponteiro para as senhas j� chamadas e inicializamos alocando memoria do tamanho de uma strutura de SenhasChamadas
	Senha *ant = (Senha*) malloc(sizeof(Senha));  // criamos um ponteiro para uma senha e alocamos memoria do tamannho de uma strutura Senha
	ant->id = s->id; // preenchemos ela com o id da senha que foi selecionada para ser chamada
	ant->prioridade = s->prioridade; // fazemos o mesmo com a priordade
	ant->senha = s->senha; // e � claro com a senha, que � o "importante"
	ant->next = NULL; // podemos apontar para NULL pois essa senha n�o est� mas na fila de senahs a serem chamadas
	sc->senha = ant; // atribuimos o ponteiro criado acima para a fila de senhas chamadas
	sc->next = *senhasChamadas; // e apontamos para a ultima senha chamada, colocando no topo
	*senhasChamadas = sc; // e atribuimos o a nova senha chamada para a fila de senhas chamadas
	cout << "SENHA CHAMADA: " << (s->prioridade ? " P" : " N") << s->senha << "\nTIPO: " << (s->prioridade ? " PRIORITARIA" : " NORMAL") << endl; // imprimimos a senha chamada
	*senhas = excluirsenha(*senhas, s->id); // excluimos a senha chamada da fila de es
}

/*
fun�ao para listar a senhas em espera
paramentos
Senha *senhas, ponteiro para a fila de senhas
*/
void listarSenhas(Senha *senhas){
    cout << "\n---- SENHAS EM ESPERA ----\n"; // imprimi que � a fila de espera
    Senha* s; // cria um ponteiro para as senhas chamadas
    cout << "SENHA |  TIPO " << endl;  // imprimi uma legenda para a tabela
	for (s = senhas; s != NULL; s = s->next) // atrinuimos a senha para a o ponteiro s e enquanto ele n�o for nulo chamamos o proximo
		cout << "  " << (s->prioridade ? " P" : " N") << s->senha  << "   | " << (s->prioridade ? " PRIORITARIA" : " NORMAL") << endl; //imprimimos os dados da senha
}

/*
fun�ao para listar a senhas j� chamadas
paramentos
SenhasChamadas *senhasChamadas, ponteiro para a fila de senhas chamadas
*/
void listarSenhasChamadas(SenhasChamadas *senhasChamadas){
    cout << "\n---- SENHAS CHAMADAS ----\n"; // imprimi que � a fila de senhas chamadas
    SenhasChamadas* s; // criamos um ponteiro para as senhas chamadas
    cout << "ID | SENHA | TIPO " << endl; // impimimos uma leganda para a tabela
	for (s = senhasChamadas; s != NULL; s = s->next) // atrinuimos a senha chamada  para a o ponteiro s e enquanto ele n�o for nulo chamamos o proximo
		cout << " "   << (s->senha)->id << " |   " << ((s->senha)->prioridade ? " P" : " N")  << (s->senha)->senha << "   | " << ((s->senha)->prioridade ? " PRIORITARIA" : " NORMAL") << endl; //imprimimos os dados da senha
}


int main(void) { //metodo principal aonda � execultado o sistema
	Senha* senhas = inicializaSenha(); //criamos um ponteiro de para a fila de senhas e inicializamos ele
	SenhasChamadas* senhasChamadas = inicializaSenhasChamadas(); //criamos um ponteiro para a senhaChamadas e inicializamos ele
	int cp = 2; // criamos o contador para as senhas com prioridades chamadas inicializamos ela com 2 pois ao iniciar o sistema ira chamar primiro uma senha normal
	int qtdPrioridade = 0; //contador para a quantide de senhas com prioridade
	int qtdNormal = 0; //contador para a quantidade de senhas normais
	int opcao; // variavel para coletar a op��o digitada

	do{// comando para iniciar um looping chamado do-while onde ele excuta a instru��o ao menos uma vez antes de verificar a condi��o
    /*
     imprimi o menu
    */
		cout << "\n\n---- MENU PRINCIPAL ----\n\n";
	    cout << "1 - GERAR SENHA NORMAL\n";
	    cout << "2 - GERAR SENHA PRIORITARIA\n";
	    cout << "3 - CHAMAR A PROXIMA SENHA\n";
	    cout << "4 - LISTAR SENHAS EM ESPERA\n";
	    cout << "5 - LISTAR SENHAS CHAMADAS\n";
		cout << "6 - SAIR\n";
		cout << "DIGITE SUA OPCAO: ";
	    cin >> opcao; //pega a op��o digitada e atribui a op��o
		system("cls"); // limpa a tela

		switch(opcao){ // seleciona um caso para a op��o
			case 1: gerarSenha(&senhas, qtdNormal, qtdPrioridade); //caso a op��o seja 1 o sistma  gera uma senha sem prioridade
				qtdNormal++; // aumenta o contador de senha normal
				break;
			case 2: gerarSenha(&senhas, qtdNormal, qtdPrioridade, 1); //caso a op��o seja 2 o sistema gera uma senha com prioridade
				qtdPrioridade++; // aumenta o contados de senha com prioritario
				break;
			case 3: chamar(&senhas, &senhasChamadas, &cp); // caso a op��o seja 3 ele chama a pr�xima senha
				break;
			case 4: listarSenhas(senhas); // caso seja 4 ele lista as senhas que est�o na fila de espera
				break;
			case 5: listarSenhasChamadas(senhasChamadas); // caso seja 5 ele lista as senhas que j� foram chamadas
				break;
		}
	}while(opcao != 6); // ele vai rodar essas instru��es at� que a op��o digitada seja 6

	return 0;
}
