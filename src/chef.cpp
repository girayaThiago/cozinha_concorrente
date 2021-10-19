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
	//1. espera um pedido chegar (gerente)
	//2. verifica disponibilidade dos ingredientes
		//2.1 se disponivel prepara
		//2.2 se não buscar mais
	//3.devolve o pedido (implica 2 filas de pedidos, á fazer e prontos).
	//4. volta para 1.  
	return nullptr;
}


Chef::Chef(){
	id = instances++;
}

void Chef::receber_comanda(){

}
void Chef::devolver_pedido(){

}
