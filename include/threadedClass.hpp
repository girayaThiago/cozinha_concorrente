//
//  ThreadedClass.hpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 12/10/21.
//

#ifndef ThreadedClass_hpp
#define ThreadedClass_hpp


#include <pthread.h>

/// Classe base de todas as classes com threads.
/// ë necessário implementar uma função estática em cada classe que for derivada desta, para ser o ponteiro na hora de criar a thread.
class ThreadedClass {
protected:

	pthread_t thread;
	
	//static void * run(void * args); todo mundo tem que ter uma dessas
	
	void wait();
	
public:
	int id;
	virtual void start(void) = 0;
	
	void join(void);
	
};

#endif /* ThreadedClass_hpp */
