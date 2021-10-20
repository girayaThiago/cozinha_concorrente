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
	id = instances++; // truque para contar atribuir id = numero de instancias no momento de criação.
}
using namespace std;

void Garcom::start(){
	pthread_create(&thread, NULL, run, this);
}

void Garcom::atender(){
	//encaminha para o gerente
	Cliente* c = Gerente::getManager().atender_cliente();
	if (c == NULL) {
		printf("\tErro, garçom %d pegou um cliente nulo para atender\n\n", id);
		exit(-1);	
	}
	printf("\tGarçom %d atendendo cliente %d \n", id, c->id);
	sleep(rand()%2+1);
	Comanda* comanda = new Comanda(c,&c->p);
	printf("\tGarçom %d preparou comanda e enviou à cozinha\n", id);
	Gerente::getManager().comanda_para_fila(comanda);
}

void Garcom::servir(){
	Comanda* pratoPronto = Gerente::getManager().pegar_prato();
	if (pratoPronto == NULL){
		printf("\tErro, garçom %d pegou um pedido nulo\n\n", id);
		exit(-1);	
	}
	printf("\tGarçom %d pegou o prato do cliente %d\n", id, pratoPronto->c->id);
	sleep(rand()%3+1);
	sem_post(&(pratoPronto->c->sem_pedido_chegou)); //levou o prato
	delete pratoPronto;
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
			garcom.atender();
		}
		// 2 atendimento é pedido pronto 
		else {
			// 2.1 levar pedido para cliente
			garcom.servir();
		}
	}
	
	// 3 voltar para 1 enquanto restaurante aberto;
	printf("\tGarçom %d terminou\n", garcom.id);
	return nullptr;
}


