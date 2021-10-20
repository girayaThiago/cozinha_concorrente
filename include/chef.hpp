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
protected:
	
	inline static int instances = 0; //contador de instancias da classe
	static void* run(void* args); //função para ser colocada como uma thread.
	
	void preparar_proteina(Proteina p); //preparar mais proteina p e atualiza valor de forma atômica.
	void preparar_acompanhamento(Acompanhamento a); //preparar mais acompanhamento a e atualiza valor de forma atômica.
public:
	Chef();
	//herança: função que cria a thread.
	void start(void);
};


#endif /* chef_hpp */
