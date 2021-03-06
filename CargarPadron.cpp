// CargarPadron.cpp: define el punto de entrada de la aplicación de consola.
//
//Bibliotecas
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <cctype> 
#include <cstdlib>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h> 
#include <math.h>
#include <sstream>
#include <random>
using namespace std;

//T_Votante
typedef struct T_Votante { //Se define la estructura para los votantes
	char cedula[10];//se declaran las variables tipo arreglos de caracteres como atributos de las estructuras
	char codelec[7];
	char sexo;
	char fecha[9];
	char numjun[6];
	char nombre[31];
	char papellido[27];
	char sapellido[27];
	T_Votante * PtrSiguiente;//se declara un puntero siguiente, del mismo tipo de la estructuta
}*PtrT_Votante;//se declara un tipo de punteros que apuntan a este tipo de datos de la estructura



//Funcion para agregar un votante, recibe como parametro la lista de votantes y la LINEA DE TEXTO del padron electoral
//extrae cada uno de los atributos de la linea y los almacena en un nodo de la lista de votantes
void agregarvotante(PtrT_Votante &ListaV, char agregado[118]) {//funcion que no retorna valor, y recibe 2 parametros uno un puntero por referencia y otro arreglo de caracteres por valor
	PtrT_Votante Aux = new (T_Votante);//se declara un puntero y se pone a apuntar a una variable anonima del tipo de mi estructura
	Aux->PtrSiguiente = ListaV;//igualo el atributo siguiente del auxiliar al puntero del primer elemento de la lista
	ListaV = Aux;//igualo  el puntero de inicio de lista a la direccion de la variable anonima agregada por el AUX

	for (int ce = 0; ce<9; ce++) {//ciclo que se repite 9 veces con un contador
		ListaV->cedula[ce] = agregado[ce];//agrega con el contador al atributo arreglo del elemento los caracteres del arreglo psados por metodos
	}
	ListaV->cedula[9] = '\0';//se agrega caracter que indica el final de la cadena

	for (int co = 10; co < 16; co++) {//utilizo atro ciclo for para recorrer los caracteres del archivo y egragar los al atributo arreglo de la variable anonima
		ListaV->codelec[co - 10] = agregado[co];//al igual que en el caso anterior
	}
	ListaV->codelec[6] = '\0';//se agrega caracter que indica el final de la cadena

	ListaV->sexo = agregado[17];//se agrega el caracter al atributo en la pocision 17 del parametro


	for (int fe = 19; fe < 27; fe++) {
		ListaV->fecha[fe - 19] = agregado[fe];
	}
	ListaV->fecha[8] = '\0';

	for (int nu = 28; nu < 33; nu++) {
		ListaV->numjun[nu - 28] = agregado[nu];
	}
	ListaV->numjun[5] = '\0';

	for (int nom = 34; nom < 64; nom++) {
		ListaV->nombre[nom - 34] = agregado[nom];
	}
	ListaV->nombre[30] = '\0';

	for (int pa = 65; pa< 91; pa++) {
		ListaV->papellido[pa - 65] = agregado[pa];
	}
	ListaV->papellido[26] = '\0';

	for (int sa = 92; sa < 118; sa++) {
		ListaV->sapellido[sa - 92] = agregado[sa];
	}
	ListaV->sapellido[26] = '\0';

	/*al igual en cada caso, se leen con ciclos caracteres especificos del arreglo parametro y se agregan a los atributos de la variable y se agrega el caracter del final del arreglo*/
}



//Funcion para cargar los votantes, se encarga de tomar cada una de las lineas
//directo del archivo de texto y enviarlo a la funci�n encargada de extraer cad uno
// de los datos e incorporarlos en un nodo de la lista.
void CargarVotantes(PtrT_Votante &ListaV) {//funcion que no retorna valor y recibe como parametro un puntero tipo PtrVotante
	int cont = 1;//declaro contador e inicializo en 1
	time_t inicio, fin;//declaro 2 variables del tipo time_t agragadas de la libreria time
	inicio = time(NULL);//asigno el valor a la variable de la funcion time con el parametro nulo
	FILE *archivo;//declara puntero a archivo
	fopen_s(&archivo, "PADRON_COMPLETO.txt", "r");//abro el archivo de texto en modo lectura y con su nombre
	if (NULL == archivo) {//condicional para verificar la creacion del archivo
		printf("No se pudo abrir el archivo");
	}
	else {//en caso de que exista
		char agregado[119];//se declara un arreglo de caracteres
		while (fgets(agregado, 119, archivo) != NULL) {
			if (cont % 2 != 0) {//-*-*-*-*-*-**-*-*-*---*-*-*---*-*-*-*-*-*-*-**-*-*-*-*-*-*-*-*+*+*+*+*+*+*+*+*+*-*-*+*+*-+*+*+*-*-**-*-*-*-*+**+*-**-**-***+*-*-*+**-*-*+**-*-*+
				agregarvotante(ListaV, agregado);
			}
			cont++;
		}
		fclose(archivo);//se cierra el archivo
	}

	fin = time(NULL);//asigno el valor a la variable de la funcion time con el parametro nulo

	cout << "----------------------------Padron cargado--------------------------------" << endl;
	printf("\nEl cargado del padron ha tardado : %f segundos.\n", difftime(fin, inicio));//imprimo el valor retornado por la funcion que resta los tiempos guardados en las variables
	//calculando asi el tiempo de carga o de ejecucion de esta seccion del codigo
	cout << "----------------------------Padron cargado--------------------------------" << endl;
	system("pause");//se pausa el sistema esperando respuesta del usuario
}


//Funcion para liberar los votantes en estructuras de memoria dinamica de la lista enlazada hasta dejar la lista en NULL

void LiberarVotantes(PtrT_Votante &ListaV) {
	PtrT_Votante Aux = ListaV;
	time_t inicio, fin;

	inicio = time(NULL);//asigno el valor a la variable de la funcion time con el parametro nulo

	while (Aux != NULL) {
		ListaV = ListaV->PtrSiguiente;
		delete(Aux);
		//Globalfree(Aux);
		Aux = ListaV;
	}

	fin = time(NULL);//asigno el valor a la variable de la funcion time con el parametro nulo

	cout << "----------------------------Padron liberado--------------------------------" << endl;
	printf("\nLa liberacion del padron ha tardado : %f segundos.\n", difftime(fin, inicio));//imprimo el valor retornado por la funcion que resta los tiempos guardados en las variables
	//calculando asi el tiempo de carga o de ejecucion de esta seccion del codigo
	cout << "----------------------------Padron liberado--------------------------------" << endl;
	system("pause");
}


//Funci�n para inicializar la lista de votantes
void inicializarvotantes(PtrT_Votante &ListaV) {//funcion que no retorna valor y que recibe de parametros un puntero por referencia
	ListaV = NULL;//puntero lista re pone a apuntar a la direccion null
}


PtrT_Votante BuscarVotante(PtrT_Votante &Lista, char cual[9])
{
	bool encontro = false;
	PtrT_Votante Aux;
	Aux = Lista;

	while ((!encontro == true) && (Aux != NULL))
	{
		if (strncmp(Aux->cedula, cual, 9) == 0)
			encontro = true;
		else
			Aux = Aux->PtrSiguiente;
	}
	return Aux;
}



void main() {//funcion principal no retorna valor
	bool realizado = false;
	bool ciclo = true;
	int opcion = 0;
	PtrT_Votante ListaV;
	inicializarvotantes(ListaV);
	cout << "Por favor espere mientras se carga el Padron" << endl;
	CargarVotantes(ListaV);

	PtrT_Votante Encontrado = NULL;
	char cedbusq[10] = "305160712";
	
	Encontrado = BuscarVotante(ListaV, cedbusq);
	if (Encontrado != NULL) {
		cout << endl << "Encontre' al Votante!! " << endl << endl;

		cout << "Ce'dula: " << Encontrado->cedula << endl;
		cout << "Nombre: " << Encontrado->nombre << endl;
		cout << "Primer Apellido: " << Encontrado->papellido << endl;
		cout << "Segundo Apellido: " << Encontrado->sapellido << endl;
		cout << "Sexo: " << Encontrado->sexo << endl;
		cout << "Fecha: " << Encontrado->fecha << endl;
		cout << "Co'digo Electoral:  " << Encontrado->codelec << endl;
		cout << "Nu'mero Junta: " << Encontrado->numjun << endl;
	}
	else
		cout << " No se encontro al votante !!! " << endl;
	LiberarVotantes(ListaV);

	cout << "Finalizado" << endl;//se imprime un mensaje para indicar la finalizacion
	system("pause");//se pausa el sistema hasta alguna entrada del usuario


}

//RESULTADO PRIMERA EJECUCION(AGREGANDO AL INICIO)

/*Por favor espere mientras se carga el Padron
----------------------------Padron cargado--------------------------------

El cargado del padron ha tardado : 70.000000 segundos.
----------------------------Padron cargado--------------------------------
Presione una tecla para continuar . . .

Encontre' al Votante!!

Ce'dula: 305160712
Nombre: CARLOS ALBERTO
Primer Apellido: CORONADO
Segundo Apellido: ZUÐIGA
Sexo: 1
Fecha: 20270126
Co'digo Electoral:  301031
Nu'mero Junta: 03492
----------------------------Padron liberado--------------------------------

La liberacion del padron ha tardado : 2.000000 segundos.
----------------------------Padron liberado--------------------------------
Presione una tecla para continuar . . .

*/