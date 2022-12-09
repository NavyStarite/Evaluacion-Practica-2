#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct Producto{
	int ID;
	char NOMBRE[50];
	int UNIDADES;
	int PRECIO;
	char CADUCIDAD[10];
}Producto;

typedef struct Hash{
	Producto PROD;
	int Vacio;
}Hash;

typedef struct Nodo_Cola{
	Producto dato;
	struct Nodo_Cola * siguiente;
}Nodo_Cola;



typedef struct{
	Nodo_Cola * primero;
	Nodo_Cola * ultimo;
}Cola;

typedef Cola *COLA;

void llenarTabla(Producto *entrada,Hash *hash,int);
int buscarTabla(int,int,Hash *hash);
int hashNumber(int,int);

COLA crearCola();
Nodo_Cola * crearNodoCola();
int es_vaciaCola(COLA);
void encolar(COLA, Producto);
Producto primero(COLA);
Producto desencolar(COLA);
void imprimirCola(COLA, COLA);

void main(){

	char buffer[200];
	char *cutString;

    COLA listaCola,aux;
    int opcion,ex=0,auxiliar=0;
	Producto dato;
    listaCola = crearCola();
    aux = crearCola();

	int sizeOfHash;
	FILE* baseD = fopen("base.txt", "r");
	if (baseD == NULL) {//Revisa que el archivo no sea nulo
        printf("No existe el archivo.");
        return 0;
    }

	while (feof(baseD) != 1)
    {
        fgets(buffer, 200, baseD);
		sizeOfHash++;
    }

	Producto *Productos = malloc(sizeOfHash*sizeof(Producto));//Creo el array
	Hash *TablaHash = malloc(sizeOfHash*sizeof(Hash));//Creo el array
  	if (Productos == NULL) {
    	printf("No se pudo reservar la memoria\n");
  	}

	baseD = fopen("base.txt", "r");
	while (feof(baseD) != 1)
    {
        fgets(buffer, 200, baseD);

        Productos[auxiliar].ID = atoi(strtok(buffer, ","));
        strcpy(Productos[auxiliar].NOMBRE,strtok(NULL, ","));
		Productos[auxiliar].UNIDADES = atoi(strtok(NULL, ","));
		Productos[auxiliar].PRECIO = atoi(strtok(NULL, ","));
		Productos[auxiliar].UNIDADES = strtok(NULL, ",");
		auxiliar++;
    }


    printf("Bienvenido al simulador de estructura de datos \"Cola\".\n¿Que deseas realizar?\n");   
    do{

		

		printf("1.-Mostrar Infromacion\n");
    	printf("2.-Almacenar Productos\n");
    	printf("3.-Eliminar Dato\n");
    	printf("4.-Hacer Compra\n");
		printf("5.-Salir\n");
		scanf("%d",&opcion);
    		switch(opcion){
			case 1:
            	imprimirCola(listaCola,aux);
            
        break;
        case 2:
            printf("ALMACENAR\n\n");
			printf("Introduzca el dato que desea añadir\n");
			scanf("%d",&dato);
            encolar(listaCola,dato);
        break;
        case 3:
            printf("ELIMINAR\n\n");
            printf("Se desencolo el numero %d.\n",desencolar(listaCola));
        break;
		case 4:
            printf("COMPRAR\n\n");
        break;
        default:
            ex=1;
        break;
    }




	}
	while (ex==0);
}

void imprimirCola(COLA c, COLA aux){
	int contador=0;
	Producto auxDato;
	printf("IMPRIMIR\n\n");
	            contador=0;
				if(es_vaciaCola(c)==0){
					do{
            	    encolar(aux,desencolar(c));
	        	}
	        	while (es_vaciaCola(c)==0);
            	do{
                	auxDato = desencolar(aux);
	                printf("%d.- Dato: %d\n",contador,auxDato);
    	            contador++;
        	        encolar(c,auxDato);
	        	}
		        while (es_vaciaCola(aux)==0);
				}
				else{
					printf("La cola esta vacia\n");
				}
}


COLA crearCola(){
	COLA C;
	C = (COLA) malloc(sizeof(Cola));
	if(C == NULL){
		
		exit(0);
	}
	
	C->primero = NULL;
	C->ultimo = NULL;
	return C;
}

Nodo_Cola * crearNodoCola(){
	Nodo_Cola * nvo;
	nvo = (Nodo_Cola *) malloc(sizeof(Nodo_Cola));
	if(nvo == NULL){
		
		exit(0);
	}
	return nvo;
}

int es_vaciaCola(COLA C){
	if(C->primero == NULL && C->ultimo == NULL) return 1;
	else return 0;
}


void encolar(COLA C, Producto elem){
	Nodo_Cola * nvo;
	nvo =  crearNodoCola();
	nvo->dato = elem;
	nvo->siguiente = NULL;
	if(es_vaciaCola(C)) C->primero = nvo;
	else C->ultimo->siguiente = nvo;
	
	C->ultimo = nvo;
}

Producto primero(COLA C){
	Producto v;
	if(es_vaciaCola(C)){
	printf("La cola esta vacia");
		exit(0);
	}
	
	v = C->primero->dato;
	return v;	
}

Producto desencolar(COLA C){
	Producto v;
	Nodo_Cola *nvo;
	if(es_vaciaCola(C)){
		printf("La cola esta vacia\n");
		//return 0;
		exit(0);
	}
	else{
		nvo = C->primero;
	v =  nvo->dato;
	C->primero = nvo->siguiente;
	if(C->primero == NULL) C->ultimo = NULL;
	
	free(nvo);
	return v;
	}
	
	
}


void llenarTabla(Producto *DataTable,Hash *HashTable,int size){
    int counter=0;
    int auth=0;
    int colisiones=0;
    for (int i = 0; i < size; i++)
    {
        //colisiones=0;
        auth=0;
        counter=hashNumber(DataTable[i].ID,size);
        while (HashTable[counter].Vacio==1&&(auth<2))
        {
            colisiones++;
            counter++;
            if (counter>=size&&(auth<1))
            {
                counter=0;
                auth++;
            }
            
            //printf("contador: %d auth: %d\n",counter,auth);
        }
        if ((auth<2))
        {
            //printf("Colisiono %d veces\n",colisiones);
            HashTable[counter].PROD.ID = DataTable[i].ID;
            HashTable[counter].PROD=DataTable[i];
            HashTable[counter].Vacio = 1;
        }
        else{
            printf("No se pudo ingresar el valor %d %s\n",DataTable[i].ID,DataTable[i].NOMBRE);
        }
    }
    //printf("Colisiono %d veces\n",colisiones);
}

int buscarTabla(int key, int size,Hash *HashTable){
    int auth=0;
    int counter=hashNumber(key,size);
    while (HashTable[counter].PROD.ID=key&&auth<2)
    {
        
        counter++;
        if (counter>=size)
        {

            counter=0;
            auth++;
        }
        
        //printf("contador: %d auth: %d\n",counter,auth);
    }
    //printf("contador: %d auth: %d\n",counter,auth);
    if (!(auth<2))
    {
        printf("No existe el valor de llave  %d\n", key);
        exit(0);
    }
    return counter;
}


int hashNumber(int n,int size){
    return(n%size);
}