//
//  main.cpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 23/09/21.
//

#include <iostream>
#include "../include/cliente.hpp"
#include "../include/chef.hpp"
#include "../include/garcom.hpp"
#include "../include/locksmith.hpp"

#define N_CLIENTES 12

using namespace std;

int main(int argc, const char * argv[]) {
	srand(NULL);
	Cliente clientes[N_CLIENTES];
	Chef chefs[2];
	Garcom garcons[4];
	
	pthread_rwlock_wrlock(&Locksmith::barrier_lock);
	for (auto & c : clientes) c.start();
//	for (auto & c : chefs) c.start();
//	for (auto & g : garcons) g.start();
	
	pthread_rwlock_unlock(&Locksmith::barrier_lock);
	for (auto & c : clientes) c.join();
//	for (auto & c : chefs) c.join();
//	for (auto & g : garcons) g.join();
	
	
}
