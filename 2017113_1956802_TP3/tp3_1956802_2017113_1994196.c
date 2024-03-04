#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
////  1956802
//// 2017113
///  1994196

sem_t * mutex;
sem_t * redact;
sem_t * tour;

int nbl = 0;


void * acces_bd_lecture(int id_boucle,int tid){
    sem_wait(tour);//P(tour)
    sem_wait(mutex); //P(mutex)
    if(nbl == 0) {
        sem_wait(redact);// P(redact)
    }
    sem_post(tour);//V(tour)
    nbl ++;
    sem_post(mutex); // V(mutex)

    sleep(1); //Zone critique
    sem_wait(mutex);
    nbl --;

    if(nbl == 0) {
        sem_post(redact); // V(redact)
    }

    sem_post(mutex); // V(mutex)

    printf("Acces en lecture reussi avec ID : %d  ID boucle :%d! \n",tid,id_boucle);
    return NULL;
}

void * acces_bd_ecriture(int id_boucle,int tid){
    sem_wait(tour); //P(tour)
    sem_wait(redact); //P(redact)
    sem_post(tour); // V(tour)

    sleep(1); //zone critique
    sem_post(redact); //V(redact)
    printf("Acces en ecriture reussi avec ID : %d  ID boucle :%d! \n",tid,id_boucle);
    return NULL;
}


////////////////



//Q2
void* acces_bd(){

    printf("Acces fait! \n");
    return NULL;
}

//Q3
void* acces_bd1(int id_boucle,int tid){

printf("Acces fait avec Id thread : %d   Id boucle : %d \n",(unsigned int)tid,id_boucle);
return NULL;
}

//Acces bd avec semaphore 

void* acces_bd2(int id_boucle,int tid, sem_t * sem){

sem_wait(sem);

printf("Acces section critique avec Id thread : %d   Id boucle : %d \n",(unsigned int)tid,id_boucle);

sem_post(sem);

return NULL;
}

struct Thread {

pthread_t tid;
int id_boucle;
sem_t * sem;


};


void* Wrapper(void* castedParam){
    struct Thread* param = (struct Thread*) castedParam;
    return acces_bd1(param->id_boucle,param->tid);
}

//Wrapper avec semaphore
void* Wrapper1(void* castedParam){
    struct Thread* param = (struct Thread*) castedParam;
    return acces_bd2(param->id_boucle,param->tid,param->sem);
}

//Wrapper pour la partie c
void* Wrapper2(void* castedParam){
    struct Thread* param = (struct Thread*) castedParam;
    return acces_bd_lecture(param->id_boucle,param->tid);
}

void* Wrapper3(void* castedParam){
    struct Thread* param = (struct Thread*) castedParam;
    return acces_bd_ecriture(param->id_boucle,param->tid);
}

//Q4
sem_t* init_sem() {
    sem_t* sem = calloc(1,sizeof(sem_t));
     sem_init(sem,0,1);
     return sem;
 
}

//Q5
void detruire_sem(sem_t* sem){
    free(sem);
    sem_destroy(sem);
}



//Q1 : Il peut y avoir 1 acces simultane en ecriture, car le partage de plusieur objet en lecture et ecriture pourrait causer des resultat incoherents.
// Il y a alors condition de concurrence. Pour prevenir cela, l'acces doit se faire en exclusion mutuelle.


int main(){
//Les variables 
sem_t* semaphore;
pthread_t t[10] ;
struct Thread mesparams[10] ;
semaphore = init_sem();
//Partie C
struct Thread mesparams1[10];
struct Thread mesparams2[10];

mutex = init_sem();
redact = init_sem();
tour = init_sem();

//Threads lecture
for (size_t i = 0; i < 10; i++)
{
    /* code */
    mesparams[i].id_boucle =i;
    mesparams1[i].sem = mutex;
    //mesparams1[i].sem = redact;
    //mesparams1[i].sem = tour;
    if(pthread_create(&mesparams1[i].tid,NULL,Wrapper2,(void*) &mesparams[i])!= 0)
        return -1;

}

//Threads ecriture 
for (size_t i = 0; i < 10; i++)
{
    /* code */
    mesparams2[i].id_boucle =i;
    mesparams2[i].sem = redact;
    mesparams2[i].sem = tour;
    if(pthread_create(&mesparams2[i].tid,NULL,Wrapper3,(void*) &mesparams[i]) != 0)
        return -1;

}

for (size_t i = 0; i < 10; i++)
{
    pthread_join(mesparams1[i].tid,NULL);
}

for (size_t i = 0; i < 10; i++)
{
    pthread_join(mesparams2[i].tid,NULL);
}
    detruire_sem(semaphore);
    detruire_sem(mutex);
    detruire_sem(redact);
    detruire_sem(tour);
    return 0;
}
