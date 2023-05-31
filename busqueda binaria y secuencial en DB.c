#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <time.h>

FILE* fp;
char ID[34596][50];
int id_int[34595];
char ch;
char search[20];
int contador = 0;
int pos[1000];
int pointer = 0;

void buscar();  //Busqueda Secuencia
void binaria(); //Busqueda Binaria
void leer_archivo(); //Obtener informacion del archivo
void ordenar_archivo(); // Ordenar los ID


int main() {
    int opc;

    fp = fopen("AGUASCALIENTES.txt", "r+"); //modo lectura
    leer_archivo();  // Primero hay que obtener la informacion de interes del archivo
    ordenar_archivo(); //vamos a ordenar el archivo para poder realizar una busqueda
    // Binaria, no recomiendo que esta organizacion se haga dentro de la funcion que hace la busqueda
    // porque cada que se haga una busqueda binaria va a organizar los datos y esto tomaria
    //mucho tiempo, si lo hacemos al inicio de todo, se podra realizar la busqueda binaria
    //mas rapido y todas las veces que sean necesarias
    do {
        system("cls");
        printf("\t****Base de Datos de Aguascalientes****\n\n");
        printf("\n 1.- Buscar un ID de una persona de forma secuencial");
        printf("\n 2.- Buscar un ID de una persona de forma binaria");
        printf("\n 3.- Salir");

        printf("\n Opcion a escoger: ");
        scanf("%i", &opc);
        system("cls");

        switch (opc) {

        case 1: buscar();
            break;

        case 2: binaria(); 
            break;

        }

    } while (opc != 3);

    fclose(fp);  // Es importante cerrar el archvo despues de usarlo

    system("pause");
    return 0;
}

void leer_archivo() {
    int i = 0, j = 0;
    do
    {
        ch = fscanf(fp, "%s", ID[i]); //Con esta funcion se van obteniendo todos los string
                                       //del documento separados por espacio
        if (j == 20) {                  // Hay 20 datos de cada persona, por eso el 20, no vamos a usarlos todos
            j = 1;
            i++;
        }
        else {
            j++;;
        }
            

    } while (ch != EOF);
    

}

void ordenar_archivo() { // Para la busqueda binaria es necesario tener el archivo ordenado, lo ordenamos con el
                        //metodo de la burbuja y esta de menor a mayor, esto solo se realiza una vez y queda listo
                        //para usarse las veces necesarias
    int aux;
    int i,j;
    unsigned t1, t2;
    t1 = clock();
    for (i = 0; i < 34595; i++) {
        id_int[i] = (int) strtol(ID[i], NULL, 10);  //del archivo txt obtuvimos string, hay que hacer un cast a entero 
                                                    //para poder ordenar los numeros
    }
    
    for (i = 0; i < 34595; i++) {       //Metodo de la burbuja organizados de menor a mayor
        for (j = 0; j < 34595; j++) {
            if (id_int[j] > id_int[j + 1]) {
                aux = id_int[j + 1];
                id_int[j + 1] = id_int[j];
                id_int[j] = aux;
            }
        }
    }

    t2 = clock();
    double segundos = (t2 - t1)/ CLOCKS_PER_SEC;
 
    printf("\nEl tiempo utilizado en segundos fue: %.9f \n", segundos);
    system("pause");

}

void buscar() {  //Busqueda secuencial, en este caso si se realiza la comparacion entre strings
    unsigned t1, t2;
    
    system("cls");
    printf("Digita el ID que estas buscando: ");
    scanf("%s", &search);
    contador = 0;
    int no_found = 1;
    int i;
    t1 = clock();
    for (i = 0; i < 34595; i++) {
        contador++;         //Para indicar cuantas veces ha ejecutado el for, cuantas iteraciones fueron necesarias
        if (strcmp(ID[i], search) == 0) {
            no_found = 0;
            break;
        }

    }
    t2 = clock();
    double segundos = (t2 - t1) / CLOCKS_PER_SEC;
    if (no_found == 1)
        printf("'%s' NO fue encontrado \n", search);
    else
    {
        
        printf("\nEl numero de iteraciones requeridas para encontrar el 'ID' %s fue '%i':", search, contador);
        printf("\nEl tiempo utilizado en segundos fue: %.9f \n", segundos);

    }

    system("pause");

}

void binaria() {  // Busqueda Binaria
    int lim_inf, lim_sup, middle, count_1, busqueda2, i;
    lim_sup = 345950;  // Porque esta es la cantidad de datos, no confundir con el limite de los valores de la lista
    lim_inf = 0;
    count_1 = 0;
    int no_found = 1;
    unsigned t1, t2;
    printf("Digita el ID que estas buscando: ");
    scanf("%i", &busqueda2);
    t1 = clock();
    while (lim_inf <= lim_sup) {
        count_1++;  // Este contador para saber cuantas iteraciones fueron requeridas
        middle = (lim_inf + lim_sup) / 2;  // Posicion central


        if (busqueda2 == id_int[middle]) {
            t2 = clock();
            double segundos = (t2 - t1) / CLOCKS_PER_SEC;
            printf("\nEl numero de iteraciones requeridas para encontrar el 'ID' %i fue '%i':",busqueda2, count_1);
            printf("\nEl tiempo utilizado en segundos fue: %.9f \n", segundos);
            no_found = 0;
            break;
        }

        else if (busqueda2 < id_int[middle]) {
            lim_sup = middle - 1;
        }

        else {
            lim_inf = middle + 1;
        }



    }

    // Si no se encontro nada

    if (no_found == 1) {
        printf("ID no encontrado\n");
    }

    system("pause");

}
