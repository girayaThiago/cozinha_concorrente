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
#include "../include/gerente.hpp"
#include "../include/garcom.hpp"

using namespace std;
Cliente::Cliente() {
	id = instances++;
}


void Cliente::start(){
	pthread_create(&thread, NULL, run, this);
}

void* Cliente::run(void* args){
	Gerente &g = *(Gerente::getManager());
	Cliente &c = *((Cliente*) args);
	c.wait();
	printf("Cliente %d começou\n", c.id);
	
	//1. tenta esperar uma mesa
	if (sem_trywait(&g.sem_mesas) != 0){
		printf("Cliente %d está aguardando na fila\n", c.id);
		sem_wait(&g.sem_mesas);
	}
	printf("Cliente %d pegou uma mesa\n", c.id);
	//2. escolher o pedido
	Pedido p = c.decidir(); 
	
	// inserir cliente na fila de atendimento;
	//3. chamar garçom (post no semaforo que os garçoms estão esperando)
	
	//4. esperar garçom chegar depois de escolher
	

	

	// 5. depois de comer liberar mesa
	sem_post(&g.sem_mesas);

	printf("Cliente %d terminou\n", c.id);
	return NULL;
}

Pedido Cliente::decidir() {
	printf("Cliente %d está escolhendo o que comer\n", id);
	sleep(rand()%4+1);
	return Pedido(rand()%3, rand()%4, rand()%4); //escolhe um prato random
}
