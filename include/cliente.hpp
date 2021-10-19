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
	inline static int instances = 0;
	static void* run(void* args);
	void decidir();
	Pedido p;
public:
	
	Cliente();
	
	//inheritance
	void start(void);
};

#endif /* Cliente_hpp */
