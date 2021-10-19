//
//  locksmith.cpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 09/10/21.
//


#include "../include/gerente.hpp"

//Inicializa todos os locks;
Gerente& Gerente::getManager(){
    if (defaultManager == NULL) defaultManager = new Gerente();
    return *defaultManager;
}

Gerente::~Gerente(){
    if (defaultManager != NULL) delete defaultManager;
}
void Gerente::abrir_restaurante(){
    resturante_aberto = N_CLIENTES;
    pthread_rwlock_unlock(&barrier_lock);
}

void Gerente::cliente_para_fila(Cliente* c){
    sem_wait(&sem_controle_clientes); //concorrencia no acesso a fila
    fila_clientes.push(c);
    sem_post(&sem_controle_clientes);
    sem_post(&sem_sinal_atendimento); //adiciona na fila e avisa que precisa de atendimento;
}

Cliente* Gerente::atender_cliente(){
    sem_wait(&sem_controle_clientes);
    if (fila_clientes.empty()) return NULL;
    Cliente* c = fila_clientes.front();
    fila_clientes.pop();
    sem_post(&sem_controle_clientes);
    return c;
}

void Gerente::comanda_para_fila(Comanda* c){
    sem_wait(&sem_controle_comandas);
    fila_comandas.push(c);
    sem_post(&sem_controle_comandas);
    sem_post(&sem_sinal_cozinha); //avisa a cozinha que tem um pedido para ser feito;
}

Comanda* Gerente::pegar_comanda(){
    sem_wait(&sem_controle_comandas);
    if (fila_comandas.empty()) return NULL;
    Comanda* c = fila_comandas.front();
    fila_comandas.pop();
    sem_post(&sem_controle_comandas);
    return c;
}

void Gerente::prato_para_fila(Comanda* p){
    sem_wait(&sem_controle_pratos);
    fila_pratos_prontos.push(p);
    prioridade++;
    sem_post(&sem_controle_pratos);
    sem_post(&sem_sinal_atendimento);
}
Comanda* Gerente::pegar_prato(){
    sem_wait(&sem_controle_pratos);
    if (fila_pratos_prontos.empty()) return NULL;
    Comanda* c = fila_pratos_prontos.front();
    fila_pratos_prontos.pop();
    prioridade--;
    sem_post(&sem_controle_pratos);
    return c;
}
Gerente::Gerente(){
    
    // restaurante começa fechado;
    pthread_rwlock_wrlock(&barrier_lock);
    
    // quantidade de lugares para os clientes inicialmente;
    sem_init(&sem_mesas, 0, N_MESAS);
    
    // nenhum sinal requisitado inicialmente;
    sem_init(&sem_sinal_atendimento, 0, 0);
    sem_init(&sem_sinal_cozinha, 0, 0);
    sem_init(&sem_sinal_fim_expediente,0,0);

    //somente 1 thread pode operar por vez;
    sem_init(&sem_controle_comandas,0,1); 
    sem_init(&sem_controle_clientes,0,1);
    sem_init(&sem_controle_pratos,0,1);
    sem_init(&sem_controle_contador,0,1);
}