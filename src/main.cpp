//
//  main.cpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 23/09/21.
//

#include <iostream>
#include <random>
#include "../include/cliente.hpp"
#include "../include/chef.hpp"
#include "../include/garcom.hpp"
#include "../include/gerente.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
	srand(std::random_device()());
	Gerente& g = Gerente::getManager();
	Cliente clientes[N_CLIENTES];
	Chef chefs[N_CHEF];
	Garcom garcons[N_GARCOM];
	
	for (auto & c : clientes) c.start();
	for (auto & c : chefs) c.start();
	for (auto & g : garcons) g.start();
	g.abrir_restaurante();

	for (auto & c : clientes) c.join();
	printf("todos os clientes foram atendidos o restaurante fechou!\n");
}
