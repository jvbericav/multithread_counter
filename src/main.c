/* 
 João Vitor Berica Vicente, 199867
 Contador de números primos
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX 15

int n_threads=0;
int n_primos=0;
pthread_mutex_t trava;

void* contador(void* arg){
	int div=0;
	int* num = (int*)arg;
	/*trava para verificacao do num*/
	pthread_mutex_lock(&trava);
	for(int i=1; i<=*num; i++){
		if(*num % i ==0)
			div ++;
	}
	if(div == 2)
		n_primos++;//se for primo adiciona 1
	/*destrava para outras threads*/
	pthread_mutex_unlock(&trava); 
	n_threads--;
	return NULL;
}

int main(){
	pthread_t thread[MAX];
	int i, n, id[MAX];
	char esp=0;

	for(i=0; esp != '\n'; i++){
		scanf("%d%c", &n, &esp);
		/*o n lido chegara a thread como arg*/
		id[i] = n; 
		/*segue somente com menos de 4 threads executando*/
		while(n_threads>=4){} 
		n_threads++;
		pthread_create(&(thread[i]), NULL, contador, (void*)(&id[i]));
	}

	/*espera as todas as threads finalizarem para printar*/ 
	while(n_threads!=0){}
	printf("%d\n", n_primos);

	return 0;
}
