//
//  locksmith.hpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 09/10/21.
//

#ifndef gerente_hpp
#define gerente_hpp

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <map>
#include "../include/cliente.hpp"
#include "../include/comanda.hpp"

// classe que armazena locks globais... necessidade questionável.
class Gerente{
private:
	inline static Gerente* defaultManager = NULL;
	Gerente();
	~Gerente();
	void init();
	std::queue<Cliente*>fila_clientes;
	std::queue<Comanda*>fila_comandas;
	inline static int prioridade = 0; // controle de prioridade pedidos novos vs cuidar da cozinha;
public:
	/// Usando um lock RW como barreira para todas as classes.
	/// Todas as classes aguardam esse lock ser liberado para leitura para continuar.
	/// Assim, nenhuma thread tenta acessar nada até que tudo esteja preparado.
	inline static pthread_rwlock_t barrier_lock = PTHREAD_RWLOCK_INITIALIZER;
	
	// controle de acesso por volume;
	sem_t sem_mesas; // representa clientes que possuem uma mesa no restaurante;
	
	// controle de fluxo sinais
	sem_t sem_sinal_atendimento; // representa um sinal de atendimento (pedido pronto || cliente chamou)
	sem_t sem_sinal_cozinha; // representa um sinal de preparo para a cozinha (pedido chegou);

	//controle de acesso a variáveis
	sem_t sem_controle_clientes;
	sem_t sem_controle_comandas;

	void abrir_restaurante(); // libera as threads
	static Gerente* getManager(); //pega o singleton do gerente.
	
	void cliente_para_fila(Cliente* c);
	Cliente* atender_cliente();

	void comanda_para_fila(Comanda* c);
	Comanda* pegar_comanda();

};

#endif /* gerente_hpp */
