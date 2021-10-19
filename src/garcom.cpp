//
//  garcom.cpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 12/10/21.
//

#include "../include/garcom.hpp"
#include "../include/gerente.hpp"

Garcom::Garcom(){
	id = instances++;
}

void Garcom::start(){
	pthread_create(&thread, NULL, run, this);
}

void Garcom::pedir(Cliente* c, Pedido* p){
	//encaminha para o gerente
	Gerente::getManager()->comanda_para_fila(&Comanda(c,p));
}

void* Garcom::run(void *args){
	Gerente& g = *(Gerente::getManager());
	Garcom& a = *((Garcom*)args);
	a.wait(); // sincronia de threads global
	printf("Garçom %d começou e está esperando para atender um cliente\n", a.id);
	sem_wait(&g.sem_sinal_atendimento);
	printf("Garçom %d recebeu uma chamada para \n", a.id);
	if (g.prioridade == 0) {
		Cliente* c = g.atender_cliente();

	}
	// esperar chamada para atendimento;
	// 1 atendimento é novo pedido
		// 1.1 atender
		// 1.2 levar o pedido á cozinha (identificar o par cliente+pedido);
	// 2 atendimento é pedido pronto
		// 2.1 levar pedido para cliente
	// 3 voltar para 1 enquanto houver clientes;
	printf("Garçom %d terminou\n", a.id);
	return nullptr;
}


