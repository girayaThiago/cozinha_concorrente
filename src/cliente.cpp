//
//  Cliente.cpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 06/10/21.
//

#include "../include/cliente.hpp"
#include <unistd.h>
#include <chrono>
#include <iostream>
#include "../include/locksmith.hpp"
#include "../include/garcom.hpp"

using namespace std;
Cliente::Cliente() {
	id = instances++;
//	sem_init(&sem_pedido, 0, 0); //nenhum cliente com pedido em mente.
}


void Cliente::start(){
//	printf("Criando thread para Cliente %d\n", id);
	pthread_create(&thread, NULL, run, this);
}

void* Cliente::run(void* args){
	Cliente &c = *((Cliente*) args);
	c.wait();
	printf("Cliente %d começou\n", c.id);
//	sem_wait(&Garcom::sem_mesas); // esperar uma mesa
//	Pedido p = c.decidir(); // escolher o pedido
//	sem_post(&sem_pedido); // levanta a mão para ser atendido
//	sem_wait(&Garcom::sem_atendimento); // aguardar um garçom para atender
//	//garçom chegou passar pedido;
//	sem_wait(&Locksmith::sem_pedido); // pegou o lock para mecher nos pedidos
//	Garcom::pedir(&c, &p);
	
	
//	c.levantarMao();
//	c.pedir();
	printf("Cliente %d terminou\n", c.id);
	
	return NULL;
}

Pedido Cliente::decidir() {
	sleep(rand()%3+1);
	return Pedido(rand()%3, rand()%4, rand()%4);
}
