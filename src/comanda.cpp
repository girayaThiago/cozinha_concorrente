//
//  Comanda.cpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 16/10/21.
//

#include "../include/comanda.hpp"

Comanda::Comanda(Cliente* c, Pedido* p){
	this->p = p;
	this->c = c;
}
