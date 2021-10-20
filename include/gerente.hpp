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

#define N_CLIENTES 12
#define N_CHEF 2
#define N_GARCOM 4
#define N_MESAS 4

//limites da cozinha
#define N_PROTEINAS 3
#define N_ACOMPANHAMENTOS 4
#define MAX_PROTEINA 10
#define MAX_ACOMP 5

// classe que armazena locks globais... necessidade questionável.
class Gerente{
private:
	inline static Gerente* defaultManager = NULL;
	Gerente();
	~Gerente();
	void init();
	std::queue<Cliente*>fila_clientes;
	std::queue<Comanda*>fila_comandas;
	std::queue<Comanda*>fila_pratos_prontos;
public:
	// variaveis globais
	inline static int prioridade = 0; // controle de prioridade pedidos novos vs cuidar da cozinha;
	inline static int resturante_aberto = N_CLIENTES;
	//counting sort dos ingredientes disponíveis
	int proteinas[3];
	int acompanhamentos[4];
	/// Usando um lock RW como barreira para todas as classes.
	/// Todas as classes aguardam esse lock ser liberado para leitura para continuar.
	/// Assim, nenhuma thread tenta acessar nada até que tudo esteja preparado.
	inline static pthread_rwlock_t barrier_lock = PTHREAD_RWLOCK_INITIALIZER;
	
	// controle de acesso por volume;
	sem_t sem_mesas; // representa clientes que possuem uma mesa no restaurante;
	
	// controle de fluxo sinais
	sem_t sem_sinal_atendimento; // representa um sinal de atendimento (pedido pronto || cliente chamou)
	sem_t sem_sinal_cozinha; // representa um sinal de preparo para a cozinha (pedido chegou);
	sem_t sem_sinal_fim_expediente; // representa o fim do expediente, todos os clientes foram atendidos;
	//controle de acesso a variáveis
	sem_t sem_controle_clientes;
	sem_t sem_controle_comandas;
	sem_t sem_controle_pratos;
	sem_t sem_controle_contador;
	sem_t sem_controle_proteina;
	sem_t sem_controle_acompanhamento;

	void abrir_restaurante(); // libera as threads
	static Gerente& getManager(); //pega o singleton do gerente.
	
	void cliente_para_fila(Cliente* c);
	Cliente* atender_cliente();

	void comanda_para_fila(Comanda* c);
	Comanda* pegar_comanda();

	void prato_para_fila(Comanda* p);
	Comanda* pegar_prato();

	void fechar_resturante();
};

#endif /* gerente_hpp */
