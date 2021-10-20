//
//  Pedido.cpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 09/10/21.
//

#include "../include/pedido.hpp"
#include <string>
#include <iostream>

Pedido::Pedido(int c, int a, int b){
	id = instances++; // truque para contar atribuir id = numero de instancias no momento de criação.
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

void Pedido::print(int id){

	std::string string_pedido = "\tPedido Cliente ";
	string_pedido.append(std::to_string(id));
	string_pedido.append(" Proteina: ");
	if (prot == Carne) string_pedido.append("Carne");
	else if (prot == Porco) string_pedido.append("Porco");
	else string_pedido.append("Frango");
	string_pedido.append(" || Acompanhamentos: ");
	for (int i = 0; i < 2; i++){
		if (acomps[i] = Arroz) string_pedido.append("Arroz");
		else if (acomps[i] = Feijao) string_pedido.append("Feijao");
		else if (acomps[i] = Salada) string_pedido.append("Salada");
		else string_pedido.append("Farofa");
		if (i == 0) string_pedido.append(" e ");
	}
	string_pedido.append("\n");
	std::cout << string_pedido;
}	