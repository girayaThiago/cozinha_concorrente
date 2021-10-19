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
#include "../include/comanda.hpp"
#include "../include/threadedClass.hpp"

using namespace std;

class Chef: public ThreadedClass{
private:
	Comanda* comanda_atual;
	inline static int instances = 0;
	static void* run(void* args);
public:
	Chef();
	//inheritance
	void start(void);
};


#endif /* chef_hpp */
