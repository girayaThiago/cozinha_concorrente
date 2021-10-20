//
//  Cliente.hpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 06/10/21.
//

#ifndef cliente_hpp
#define cliente_hpp

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include "../include/pedido.hpp"
#include "../include/threadedClass.hpp"

// classe que representa o cliente.
class Cliente: public ThreadedClass {
private:
	
	static void* run(void* args); // função para thread.
	void decidir(); // decidir qual pedido fazer.
	
public:
	inline static int instances = 0; // contador de instancias.
	Pedido p; // pedido que vai fazer.
	Cliente(); // construtor padrão.
	sem_t sem_pedido_chegou; // semaforo unico do cliente que está aguardando o pedido
	//herança: função que cria a thread.
	void start(void);
};

#endif /* Cliente_hpp */
