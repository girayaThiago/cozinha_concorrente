//
//  locksmith.cpp
//  Cozinha_Concorrente
//
//  Created by Thiago Pereira Ribeiro Dantas on 09/10/21.
//


#include "../include/gerente.hpp"

//Inicializa todos os locks;
Gerente* Gerente::getManager(){
    if (defaultManager == NULL) defaultManager = new Gerente();
    return defaultManager;
}

Gerente::~Gerente(){
    if (defaultManager != NULL) delete defaultManager;
}
void Gerente::abrir_restaurante(){
    pthread_rwlock_unlock(&barrier_lock);
}

void Gerente::cliente_para_fila(Cliente* c){
    sem_wait(sem_controle_clientes); //concorrencia no acesso a fila
    fila_clientes.push(c);
    sem_post(sem_controle_clientes);
    sem_post(sem_cliente_pediu);//adiciona na fila e avisa que precisa de atendimento;
}

Cliente* Gerente::atender_cliente(){
    sem_wait(sem_controle_clientes);
    Cliente* c = fila_clientes.front();
    file_clientes.pop();
    sem_post(sem_controle_clientes);
    return c;
}

Comanda* Gerente::comanda_para_fila(Comanda* c){
    sem_wait(sem_controle_comandas);
    fila_comandas.push(c);
    Comanda* c = fila_comandas.front();
    fila_comandas.pop();
    sem_post(sem_controle_comandas);
    return c;
}

Comanda* Gerente::pegar_comanda(Comanda* c){

}

Gerente::Gerente(){
    
    // restaurante começa fechado;
    pthread_rwlock_wrlock(&barrier_lock);
    
    // quantidade de lugares para os clientes inicialmente;
    sem_init(&sem_mesas, 0, 6);
    
    // pedidos feitos por clientes inicialmente;
    sem_init(&sem_pedido_cliente, 0, 0); 

    //somente 1 pessoa pode operar nas comandas por vez;
    sem_init(&sem_controle_comandas,0,1); 
}