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
	
	// se for o primeiro garçom preparar as mesas
	if (id == 0){
		// sem_init(&sem_mesas, 0, 4); // numero de clientes que podem entrar
		// sem_init(&sem_atendimento, 0, 0); //nenhum cliente para pronto para pedir
		// sem_init(&sem_fila, 0, 1); // lock para mexer na fila de clientes
	}
}

void Garcom::start(){
	pthread_create(&thread, NULL, run, this);
}

void Garcom::pedir(Cliente* c, Pedido* p){
	
	

}

void* Garcom::run(void *args){
	Garcom& g = *((Garcom*)args);
	g.wait(); // sincronia de threads global
	printf("Garçom %d começou\n", g.id);
	sem_wait(Gerente::sem_atendimento);
	// esperar chamada para atendimento;
	// 1 atendimento é novo pedido
		// 1.1 atender
		// 1.2 levar o pedido á cozinha (identificar o par cliente+pedido);
	// 2 atendimento é pedido pronto
		// 2.1 levar pedido para cliente
	// 3 voltar para 1 enquanto houver clientes;
	printf("Garçom %d terminou\n", g.id);
	return nullptr;
}


