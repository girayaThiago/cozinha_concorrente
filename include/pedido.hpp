//
//  Pedido.hpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 09/10/21.
//

#ifndef pedido_hpp
#define pedido_hpp

#include <stdio.h>
#include <semaphore.h>

enum Proteina: int {
	Carne = 0, Porco, Frango
};
enum Acompanhamento: int {
	Arroz = 0, Feijao, Salada, Farofa
};

class Pedido {
private:
	inline static int instances = 0;
public:
	int id;
	Proteina prot;
	Acompanhamento acomps[2];
	void * c = NULL; //ponteiro maluco pro cliente;
	
	Pedido(int c, int a, int b);
//	void * getCliente(void);
};



#endif /* Pedido_hpp */
