/*
Objetivo: Implementar la primera version del algorimo de Dekker
Elaboro: Contreras Mejía David */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int num_proc;  /*variable global para el manejo de las primitivas de exclusión mutua */
//si i es mayor a lenght arreglo terminar proceso
int vector[50]; //vector global

void *proc_uno()
{
	int i = 0;
	while(i < 50)//se ejecuta indefinidamente
	{
		while(num_proc == 2); //primitiva de entrada del proceso uno
		/* entra a su región crítica */
		vector[i] = rand() % 256 + 1; //dar un valor aleatorio entre 1 y 255
		printf("modifique el valor de vector[%d] a %d\n",i, vector[i]);//imprimir valor modificado
		fflush(stdout);
		num_proc = 2; /* da turno al proc_dos de entrar a la región crítica (Primitiva de salida) */
		i++;
	}
	pthread_exit(NULL); //el hilo modifica termina su ejecucion
}

void *proc_dos()
{
	int j = 0;
	while(j < 50)
	{
		while(num_proc == 1); //primitiva de entrada del proceso dos
		/* entra a su región crítica */
		printf("lei el valor de vector[%d] y es: %d\n", j, vector[j]);
		fflush(stdout);
		num_proc = 1; /* da turno al proc_uno de entrar a la región crítica (Primitiva de salida) */
		j++;
	}
	pthread_exit(NULL); //el hilo consulta termina su ejecucion
}

int main(int argc, char const *argv[])
{	
	num_proc = 1; /* se le da turno inicial al proc_uno */
	

	for (int i=0;i<50;i++){//dandole valores iniciales al vector
		vector[i] = i;
	}

	pthread_t hiloModifica, hiloConsulta; //se declaran los identificadores de hilos
	int error;

	//se crean los hilos no se le pasan argumentos
	error = pthread_create(&hiloModifica, NULL, proc_uno, NULL);
	error = pthread_create(&hiloConsulta, NULL, proc_dos, NULL);

	//espera a que los hilos terminen
	error = pthread_join(hiloModifica,NULL);
	error = pthread_join(hiloConsulta,NULL);

	return 0;
}

/*Conclusiones
Se logro implementar el algoritmo de Deker satisfactoriamente, Se puede concluir 
que es un algoritmo para que solamente se permita a un proceso estar en la región 
crítica, esto permite que dos hilos compartan recursos sin conflictos.