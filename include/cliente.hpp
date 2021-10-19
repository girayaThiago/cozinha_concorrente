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


class Cliente: public ThreadedClass {
private:
	
	static void* run(void* args);
	void decidir();
	
public:
	inline static int instances = 0;
	Pedido p;
	Cliente();
	sem_t sem_pedido_chegou;
	//inheritance
	void start(void);
};

#endif /* Cliente_hpp */
