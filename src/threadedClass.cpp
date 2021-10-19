//
//  threadedClass.cpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 16/10/21.
//

#include <stdio.h>
#include "../include/threadedClass.hpp"
#include "../include/gerente.hpp"


void ThreadedClass::join() {
	pthread_join(thread, NULL);
}

void ThreadedClass::wait(){
	pthread_rwlock_rdlock(&(Gerente::barrier_lock));
}
