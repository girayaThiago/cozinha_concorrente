//
//  garcom.hpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 12/10/21.
//

#ifndef garcom_hpp
#define garcom_hpp

#include <stdio.h>
#include "../include/threadedClass.hpp"
#include "../include/comanda.hpp"
#include <queue> // fila

class Garcom: public ThreadedClass {
private:
	
	
	inline static int instances = 0;
	static void* run(void* args);
	static sem_t sem_fila;
	
public:
	Garcom();
	//inheritance
	void start(void);
	static void pedir(Cliente* c,Pedido* p); //recebe um pedido de um cliente
};



#endif /* garcom_hpp */
