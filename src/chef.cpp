//
//  Chef.cpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 23/09/21.
//

#include "../include/chef.hpp"

void Chef::start(){
	pthread_create(&thread, NULL, run, this);
}

void* Chef::run(void *args){
	Chef& c = *((Chef*)args);
	c.wait();
	printf("Chef %d começou\n", c.id);
	//loop de execução
	return nullptr;
}


void Chef::prepara(Pedido p){
	
}

int Chef::confere(Pedido p){
	//verificar a disponibilidade dos ingredientes
	//se faltar um produzir mais. se o estoque ficar crítico, pedir mais.
	//se já estiver sendo produzido, passar para o proximo pedido.
	return 0;
}

Chef::Chef(){
	id = instances++;
}

void Chef::recebe(Pedido p){
	if (confere(p)){
		prepara(p);
	} else {
		
	}
	
}
