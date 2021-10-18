//
//  garcom.cpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 12/10/21.
//

#include "../include/garcom.hpp"

Garcom::Garcom(){
	id = instances++;
	
	// se for o primeiro garçom preparar as mesas
	if (id == 0){
//		sem_init(&sem_mesas, 0, 4); // numero de clientes que podem entrar
//		sem_init(&sem_atendimento, 0, 0); //nenhum cliente para pronto para pedir
//		sem_init(&sem_fila, 0, 1); // lock para mexer na fila de clientes
	}
}

void Garcom::start(){
	pthread_create(&thread, NULL, run, this);
}

void Garcom::pedir(Cliente* c, Pedido* p){
//	sem_wait(&sem_fila);
//	Comanda comanda = Comanda(c,p);
//	fila_atendimento.emplace(comanda);
	
//	sem_post(&sem_fila);
}

void* Garcom::run(void *args){
	Garcom& g = *((Garcom*)args);
	g.wait();
	printf("Garçom %d começou\n", g.id);
//	sem_wait(&Cliente::sem_pedido);
	
	
	return nullptr;
}


