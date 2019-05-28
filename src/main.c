#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define n_threads 4

pthread_mutex_t trava;

int contador = 0;
int tam=0;
int start_threads=0;
long int entrada[50];

int primo(int numero) {
  int div = 0;
  for (int i=1; i <= numero; i++){
    if(numero % i == 0){
    div++;
    }
}
  if(div == 2){
    return 1;    
  }
  else return 0;
}


int conta_primo(int numero){
	if(primo(numero)==1){
		contador++;
	}
	return primo(numero);	
}

int j=0;

void* funcao_thread(void *arg) {
  int* N = (int*)arg;
  int M = (*N);
  /*printf("\n--------------------------\n\nThread no i = %d\n", M);*/  
while(j<tam){
    /*printf(" j = %d\n", j);*/
    pthread_mutex_lock(&trava);
    int a = conta_primo(entrada[j]);
    /*printf(" Entrada no: %li\n Primo? (1/0): %d\n Indice j = %d\n Tamanho = %d\n\n", entrada[j], a, j, tam);*/
    pthread_mutex_unlock(&trava);
    j++;
    break;
  }
  

  /*printf("Saindo da thread %d\n", M);*/
  return NULL;
}



int main(int argc, char **argv) {

pthread_t threads[n_threads];

char espaco;
int i=0;

/*Ler entrada*/

for(int b=0; b<50; b++){
entrada[b] = 0;
}


while(1){
 scanf("%li", &entrada[tam]);
 tam++;
 espaco =  getchar();
 if(espaco == '\n'){
	break;
 }
 }

/*for(int b=0; b<tam; b++){
printf("Entrada[%d] = %li\n",b, entrada[b]);}*/


/*Criando as threads, analisando quantas serao necessárias*/

/*printf("tam = %d\n",tam);*/

if(tam < n_threads){
	start_threads = tam;
}
else{
	start_threads = 4;
}


/*Criando o numeros de threads que vão trabalhar*/

  int ind[start_threads];

while(j <tam){
  for(i = 0; i < start_threads; i++) {
    ind[i] = i;
    /*printf("Indice i = %d\n", ind[i]);*/
    pthread_create(&(threads[i]), NULL, funcao_thread, &(ind[i]));
    if(i>3){
	i=0;
    }
  }
}


for(int d; d < start_threads; d++){
		pthread_join(threads[d], NULL);
	}

printf("%d\n", contador);
return 0;
}











