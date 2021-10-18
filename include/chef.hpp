//
//  chef.hpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 23/09/21.
//

#ifndef chef_hpp
#define chef_hpp

#include <stdio.h>
#include <string>
#include "../include/pedido.hpp"
#include "../include/threadedClass.hpp"

using namespace std;

class Chef: public ThreadedClass{
private:
	inline static int instances = 0;
	static void* run(void* args);
	int confere(Pedido p);
	void prepara(Pedido p);
public:
	void recebe(Pedido p);
	
	Chef();
	//inheritance
	void start(void);
};


#endif /* chef_hpp */
