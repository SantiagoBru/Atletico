/*Se obtiene información sobre los corredores que asisten a una prueba atletica durante un día con la siguiente estructura:
	NroCorredor, Documento, tiempo, sexo
Esta información se carga en una pila en la medida que llegan a la meta.

Se deberá:
- Hacer la operatoria de llegada de los corredores y su almacenamiento en la pila a medida que terminan la prueba.
- Una vez que todos concluyen la prueba pasar la información a una lista ordenada por NroCorredor 
- En forma recursiva contar la cantidad de minutos totales que insumieron todos los competidores en ese día.
- En forma recursiva contar los corredores del sexo masculino que emplearon mas de 40 minutos en finalizar.
- Calcular el porcentaje de estos últimos respecto al total de corredores de ambos sexos.
*/	



/* ESTRATEGIA 
La idea es crear un registro de tipo corredor que englobe todos los datos pedidos del corredor (DNI, tiempo, sexo y Numero de corredor).
Luego tratar como objeto ese registro e ir agregandolo a la pila a medida que se ingresan, para eso la pila recibira
como parametro de entrada el "objeto" corredor.
Luego se desapila y a su vez se ingresa ordenado a una lista por Numero de corredor.
Despues realizo una suma recursiva, para tomar la cantidad total de minutos que insumieron los corredores en ese dia. Y tambien de la misma manera, 
cuento los corredores del sexo masculino que emplearon mas de 40 minutos en finalizar.
Y por ultimo calculo el porcetaje de los anteriores corredores, respecto al total de corredores.
*/

#include <stdio.h>
#include <stdlib.h>

//Defino el Registro
struct corredor{
          int nro_corredor;
          double nro_DNI;
          float nro_tiempo;
          int sexo;
} ;

//Defino la LISTA
struct nodoLista{
          struct corredor valor;
          struct nodoLista *siguiente;
} ;

//para revisar si la lista esta vacia
int ListaVacia(struct nodoLista *lista) {
   return (lista == NULL);
} ;

//Defino la PILA
struct nodoPila {
   struct corredor valor;
   struct nodoPila *siguiente;
} ;

//para revisar si la pila esta vacia
int esvaciaPila(struct nodoPila *pila)
{	struct nodoPila *nodo;
   nodo = pila;
   if(nodo==NULL) return 0; // Si no hay nodos en la pila retornamos 0
   else return 1;
}

void apilar(struct nodoPila **pila, struct corredor o) {
   struct nodoPila *nuevo;
   // Crear un nodo nuevo
   nuevo=malloc(sizeof(struct nodoPila));
   nuevo->valor = o;

   // Añadimos la pila a continuacion del nuevo nodo
   nuevo->siguiente = *pila;
   // Ahora, el comienzo de nuestra pila es en nuevo nodo
   *pila = nuevo;
}

struct corredor desapilar(struct nodoPila **pila) {
   struct nodoPila *nodo; /* variable auxiliar para manipular nodo */
   struct corredor o;      /* variable auxiliar para retorno */
   
   nodo = *pila; /* Nodo apunta al primer elemento de la pila */
   if(!nodo) return o; /* Si no hay nodos en la pila retornamos 0 */
   /* Asignamos a pila toda la pila menos el primer elemento */
   *pila = nodo->siguiente;
   /* Guardamos el valor de retorno */
   o = nodo->valor;
   /* Borrar el nodo */
   free(nodo);
   return o;
}

//Insertar Ordenado en la lista
void InsertarOrdenadoLista(struct nodoLista **lista,struct corredor o) {
   struct nodoLista *nuevo, *anterior;

   /* Crear un nodo nuevo */
   nuevo = malloc(sizeof(struct nodoLista));
   nuevo->valor = o;

   /* Si la lista esta vacia */
   if(ListaVacia(*lista) || (*lista)->valor.nro_corredor > o.nro_corredor) {
      /* Añadimos la lista a continuacion del nuevo nodo */
      nuevo->siguiente = *lista;
      /* Ahora, el comienzo de nuestra lista es en nuevo nodo */
      *lista = nuevo;
   } else {
      /* Buscar el nodo de valor menor a v */
      anterior = *lista;
      /* Avanzamos hasta el ultimo elemento o hasta que el siguiente tenga
         un valor mayor que v */
      while(anterior->siguiente && anterior->siguiente->valor.nro_corredor <= o.nro_corredor)
         anterior = anterior->siguiente;
      /* Insertamos el nuevo nodo despues del nodo anterior */
      nuevo->siguiente = anterior->siguiente;
      anterior->siguiente = nuevo;
   }
}

//funcion de ayuda para mostrar la lista
void MostrarLista(struct nodoLista *lista) {
   //lNodo nodo = lista;

   if(ListaVacia(lista)) printf("Lista vacia\n");
   else {
      while(lista) {
         printf("%i %f-> ", lista->valor.nro_corredor,lista->valor.nro_tiempo);
         lista = lista->siguiente;
     }
     printf("\n");
   }
}


//devuelve el total de los minutos
int Totalminutos(struct nodoLista *lista)
{ int sum=0;
     if(ListaVacia(lista)) printf("Lista vacia\n");
   else {
      while(lista) {
         sum = sum + lista->valor.nro_tiempo;
         lista = lista->siguiente;
     }

   }
   return sum;
}

//devuelve el total de los corredores
int Totalcorredores(struct nodoLista *lista)
{ int sum=0;
     if(ListaVacia(lista)) printf("Lista vacia\n");
   else {
      while(lista) {
         sum = sum + 1;
         lista = lista->siguiente;
     }

   }
   return sum;
}


//suma recursivamente la cantidad de paquetes con destino 1900
int ContminHombres40min(struct nodoLista *lista) {
   //lNodo nodo = lista;

   if(ListaVacia(lista)) return 0;
   else {
      if(lista->valor.sexo == 1 && lista->valor.nro_tiempo >= 40) {
            //cuento si el paquete es del vehiculo buscado
         return 1 + ContminHombres40min(lista->siguiente);
      //sigo la recursividad con 0 si no
     } else return 0 + ContminHombres40min(lista->siguiente);

   }
}


int main(){
	struct corredor c;
    int cont=1; //por lo menos carga 1 corredor
    struct nodoPila *P = NULL;
    struct nodoLista *L =  NULL,
    
    while (cont==1){
    	printf("Ingrese el numero del corredor\n");
    	scanf("%i",&c.nro_corredor);
    	printf("Ingrese el Sexo: Masculino = 1 o Femenino = 0\n");
    	scanf("%i",&c.sexo);
    	printf("Ingrese el tiempo realizado\n");
    	scanf("%f",&c.nro_tiempo);
    	printf("Ingrese el DNI del corredor\n");
    	scanf("%d",&c.nro_DNI);
    	
    	apilar(&P,c);
    	
    	printf("Desea agregar otro corredor? 1=si 0=no\n");
    	scanf("%i",&cont);

	}
	
	 //termina la carrera

    while(esvaciaPila(P))
    {
        InsertarOrdenadoLista(&L,desapilar(&P));
    }
    
    
    
    // MostrarLista(L);
    
    cont = Totalminutos(L); 
        	   
        printf("En la carrera participaron: %i ", Totalcorredores(L));
        printf("La suma de los minutos de todos los corredores fue: %f ", cont);
        printf("Los hombres que tardaron mas de 40 minutos fueron: %i", ContminHombres40min(L));
        printf ("Los hombres que tardaron mas de 40 minutos son el &f del total de participantes", ContminHombres40min(L)*100/Totalcorredores(L))
    	}



}







