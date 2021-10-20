//
//  Chef.cpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 23/09/21.
//

#include "../include/chef.hpp"
#include "../include/gerente.hpp"
#include <string>

Chef::Chef(){
	id = instances++; // truque para contar atribuir id = numero de instancias no momento de criação.
}

/// cria a thread e executa a função run, passando como argumento uma referencia da instancia.
void Chef::start(){
	pthread_create(&thread, NULL, run, this);
}

// executa o comportamento da classe.
void* Chef::run(void *args){
	// recupera o gerente (acesso a variáveis globais e semáforos)
	Gerente& g = Gerente::getManager();

	// restaura referencia a instancia que gerou essa thread.
	Chef& chef = *((Chef*)args);
	
	// aguarda liberação do lock.
	chef.wait();
	printf("\t\tChef %d começou\n", chef.id);
	
	while (g.resturante_aberto){
		//1. espera um pedido chegar;
		sem_wait(&g.sem_sinal_cozinha);
		Comanda* comanda = g.pegar_comanda();
		if (comanda != NULL) {
			printf("\t\tChef %d pegou a comanda do cliente %d\n", chef.id, comanda->c->id);
			
			//2. verifica a disponibilidade dos ingredientes
			sem_wait(&g.sem_controle_proteina);
			if (g.proteinas[comanda->p->prot] < 1) 
				chef.preparar_proteina(comanda->p->prot); //se acabou repõe
			g.proteinas[comanda->p->prot]--;
			sem_post(&g.sem_controle_proteina);

			sleep(1); // demora pra servir.
			printf("\t\tChef %d serviu proteina do cliente %d\n", chef.id, comanda->c->id);
			
			//acompanhamento 1
			sem_wait(&g.sem_controle_acompanhamento);
			if (g.acompanhamentos[comanda->p->acomps[0]] < 1) 
				chef.preparar_acompanhamento(comanda->p->acomps[0]); //se acabou repõe
			
			sleep(1); // demora pra servir
			printf("\t\tChef %d serviu acompanhamento do cliente %d\n", chef.id, comanda->c->id);

			//acompanhamento 2
			g.acompanhamentos[comanda->p->acomps[0]]--;
			if (g.acompanhamentos[comanda->p->acomps[1]] < 1) 
				chef.preparar_acompanhamento(comanda->p->acomps[1]); //se acabou repõe
			g.acompanhamentos[comanda->p->acomps[1]]--;
			sem_post(&g.sem_controle_acompanhamento);

			sleep(2); // servir e finalizar prato
			
			printf("\t\tChef %d preparou o pedido do cliente %d\n", chef.id, comanda->c->id);
			
			//3.devolve o pedido.
			g.prato_para_fila(comanda);
		} 
	}
	
	return NULL;
}

void Chef::preparar_proteina(Proteina p){
	if (p == 0) printf("\t\tAcabou Carne cozinheiro %d está preparando mais.\n", id );
	else if (p == 1) printf("\t\tAcabou Porco cozinheiro %d está preparando mais.\n", id );
	else if (p == 2) printf("\t\tAcabou Frango cozinheiro %d está preparando mais.\n", id );
	else exit(-1);

	sleep(rand()%2+3);
	Gerente::getManager().proteinas[p] = MAX_PROTEINA;
}

void Chef::preparar_acompanhamento(Acompanhamento a){
	if (a == 0) printf("\t\tAcabou Arroz cozinheiro %d está preparando mais.\n", id);
	else if (a == 1) printf("\t\tAcabou Feijao cozinheiro %d está preparando mais.\n", id);
	else if (a == 2) printf("\t\tAcabou Salada cozinheiro %d está preparando mais.\n", id);
	else if (a == 3) printf("\t\tAcabou Farofa cozinheiro %d está preparando mais.\n", id);
	else exit(-1);

	sleep(rand()%2+3);
	printf("\t\tCozinheiro %d Terminou de preparar.\n", id);
	Gerente::getManager().acompanhamentos[a] = MAX_ACOMP;
}
