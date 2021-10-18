//
//  locksmith.hpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 09/10/21.
//

#ifndef locksmith_hpp
#define locksmith_hpp

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <map>

// classe que armazena tudo global
class Locksmith{
public:
	/// Usando um lock RW como barreira para todas as classes.
	/// Todas as classes aguardam esse lock ser liberado para leitura para continuar.
	/// Assim, nenhuma thread tenta acessar nada até que tudo esteja preparado.
	inline static pthread_rwlock_t barrier_lock = PTHREAD_RWLOCK_INITIALIZER;
	
//	inline static pthread_mutex_t lock_fila = PTHREAD_MUTEX_INITIALIZER;
//	static sem_t sem_cliente;
//	static sem_t sem_pedido;
//	sem_t sem_atendido;
	
	
	void init();
//		sem_init(&sem_cliente, 0, 0); //nenhum cliente
//		sem_init(&sem_pedido, 0, 0); //nenhum pedido
};

#endif /* locksmith_hpp */
