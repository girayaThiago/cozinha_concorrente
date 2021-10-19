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
	sem_init(&sem_pedido_chegou,0,0);
}


void Cliente::start(){
	pthread_create(&thread, NULL, run, this);
}

void* Cliente::run(void* args){
	Gerente &g = Gerente::getManager();
	Cliente* cliente = (Cliente*) args;
	printf("Cliente %d começou\n", cliente->id);
	cliente->wait();
	//1. tenta esperar uma mesa
	if (sem_trywait(&g.sem_mesas) != 0){
		printf("Cliente %d está aguardando na fila\n", cliente->id);
		sem_wait(&g.sem_mesas);
	}
	printf("Cliente %d pegou uma mesa\n", cliente->id);
	//2. escolher o pedido
	cliente->decidir(); 
	//3. inserir cliente na fila de atendimento;
	g.cliente_para_fila(cliente);

	//4. esperar pedido voltar
	sem_wait(&cliente->sem_pedido_chegou);
	printf("Cliente %d pegou seu prato e começou a comer\n", cliente->id);
	sleep(rand()%3+1);

	// 5. depois de comer liberar mesa
	sem_post(&g.sem_mesas);

	printf("Cliente %d terminou e liberou sua mesa\n", cliente->id);
	return NULL;
}

void Cliente::decidir() {
	printf("Cliente %d está escolhendo o que comer\n", id);
	sleep(rand()%4+1);
	p = Pedido(rand()%3, rand()%4, rand()%4); //escolhe um prato random
}