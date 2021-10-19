//
//  Pedido.cpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 09/10/21.
//

#include "../include/pedido.hpp"

Pedido::Pedido(int c, int a, int b){
	id = instances++;
	prot = Proteina(c);
	acomps[0] = Acompanhamento(a);
	acomps[1] = Acompanhamento(b);
}

Pedido::Pedido(){
	id = instances++;
	prot = Proteina(0);
	acomps[0] = Acompanhamento(0);
	acomps[1] = Acompanhamento(0);
}