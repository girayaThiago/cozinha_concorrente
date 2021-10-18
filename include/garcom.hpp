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
	
//	static sem_t sem_fila;
	
public:
	void pedir(Cliente* c, Pedido* p);
	std::queue<Comanda> fila_atendimento; // cada garçom tem uma fila para lembrar das suas mesas
	static sem_t sem_mesas;
	static sem_t sem_atendimento;
	Garcom();
	//inheritance
	void start(void);
	
};



#endif /* garcom_hpp */
