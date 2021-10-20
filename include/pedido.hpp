//
//  Pedido.hpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 09/10/21.
//

#ifndef pedido_hpp
#define pedido_hpp

#include <stdio.h>

// Opções de proteinas 0,1,2
enum Proteina: int {
	Carne = 0, Porco, Frango
};
// Opções de acompanhamento 0,1,2,3
enum Acompanhamento: int {
	Arroz = 0, Feijao, Salada, Farofa
};

// Representação de um pedido, 1 proteina e 2 acompanhamentos quaisquer, sem restrição de repetição.
class Pedido {
private:
	inline static int instances = 0; //contagem de instancias
public:
	int id; //id do pedido
	Proteina prot; // proteina
	Acompanhamento acomps[2]; // acompanhamentos
	
	Pedido(int c, int a, int b); //construtor especifico
	Pedido(); // construtor padrão para compliance com alocação estática de atributos de cliente.
	void print(int id);
};

#endif /* Pedido_hpp */
