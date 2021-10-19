//
//  garcom.cpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 12/10/21.
//

#include "../include/garcom.hpp"
#include "../include/gerente.hpp"
#include <unistd.h>
#include <chrono>
#include <iostream>

Garcom::Garcom(){
	id = instances++;
}
using namespace std;

void Garcom::start(){
	pthread_create(&thread, NULL, run, this);
}

void Garcom::pedir(Cliente* c, Pedido* p){
	//encaminha para o gerente
	Comanda comanda = Comanda(c,p);
	Gerente::getManager().comanda_para_fila(&comanda);
}

void* Garcom::run(void *args){
	Gerente& g = Gerente::getManager();
	Garcom& garcom = *((Garcom*)args);
	garcom.wait(); // sincronia de threads global
	printf("\tGarçom %d começou e está esperando para atender um cliente\n", garcom.id);
	
	while (g.resturante_aberto > 0){
		// esperar chamada para atendimento;
		sem_wait(&g.sem_sinal_atendimento);
		printf("\tGarçom %d recebeu uma chamada de atendimento\n", garcom.id);
		// 1 atendimento é novo pedido		
		if (g.prioridade == 0) {
			// 1.1 atender
			Cliente* c = g.atender_cliente();
			if (c != NULL) {
				printf("\tGarçom %d atendendo cliente %d \n", garcom.id, c->id);
				sleep(rand()%2+1);
				Comanda* comanda = new Comanda(c,&c->p);
				// 1.2 levar o pedido á cozinha (identificar o par cliente+pedido);
				printf("\tGarçom %d preparou comanda e enviou à cozinha\n", garcom.id);
				g.comanda_para_fila(comanda);
			}
		}
		// 2 atendimento é pedido pronto 
		else {
			// 2.1 levar pedido para cliente
			Comanda* pratoPronto = g.pegar_prato();
			if (pratoPronto != NULL){
				printf("\tGarçom %d pegou o prato do cliente %d\n", garcom.id, pratoPronto->c->id);
				sleep(rand()%3);
				sem_post(&(pratoPronto->c->sem_pedido_chegou)); //levou o prato
				delete pratoPronto;
			}
			
		}
	}
	
	// 3 voltar para 1 enquanto restaurante aberto;
	printf("\tGarçom %d terminou\n", garcom.id);
	return nullptr;
}


