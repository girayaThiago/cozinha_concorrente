//
//  Chef.cpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 23/09/21.
//

#include "../include/chef.hpp"
#include "../include/gerente.hpp"

Chef::Chef(){
	id = instances++;
}

void Chef::start(){
	pthread_create(&thread, NULL, run, this);
}

void* Chef::run(void *args){
	Gerente& g = Gerente::getManager();
	Chef& chef = *((Chef*)args);
	chef.wait();
	printf("\t\tChef %d começou\n", chef.id);
	
	while (g.resturante_aberto){
		//1. espera um pedido chegar;
		sem_wait(&g.sem_sinal_cozinha);
		Comanda* comanda = g.pegar_comanda();
		if (comanda != NULL) {
			printf("\t\tChef %d pegou a comanda do cliente %d\n", chef.id, comanda->c->id);
			//2. verifica disponibilidade dos ingredientes
				//2.1 se disponivel prepara
				//2.2 se não buscar mais
			
			sleep(2);
			printf("\t\tChef %d preparou o pedido do cliente %d\n", chef.id, comanda->c->id);
			//3.devolve o pedido.
			g.prato_para_fila(comanda);
		} 
	}
	
	return NULL;
}


