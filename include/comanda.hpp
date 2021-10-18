//
//  Comanda.hpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 16/10/21.
//

#ifndef comanda_hpp
#define comanda_hpp

#include <stdio.h>
#include "../include/cliente.hpp"
#include "../include/pedido.hpp"

class Comanda {
private:
	Pedido* p;
	Cliente* c;
public:
	Comanda(Cliente* c,Pedido* p);
};

#endif /* comanda_hpp */
