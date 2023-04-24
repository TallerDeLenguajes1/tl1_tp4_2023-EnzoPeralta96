#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Tarea
{
    int TareaID;
    char *Descripcion;
    int Duracion;
}typedef Tarea;

 struct NODO{
    Tarea T;
    struct NODO * Siguiente;

}typedef NODO;

//Declaración de funciones
NODO * CrearLista();
void InsertarNodoListaGeneral(NODO ** Lista, int ID, char *Descripcion, int Duracion);
void InsertarNodoListaParticular(NODO ** Lista, NODO * NodoAux);
NODO * AislarNodo(NODO ** Lista);
void CargarTareas(NODO ** Lista, int * ID);
int ContarTareas(NODO * Lista);
void ControlTareas(NODO ** Lista, NODO ** ListaTP , NODO ** ListaTR, int cantidadTareas);
void MostrarTareas(NODO * Lista);
NODO * BuscarXid(NODO * ListaTP, NODO * ListaTR, int ID);
NODO * Buscar_X_PalabraClave(NODO * ListaTP, NODO * ListaTR, char * Descripcion);
void buscarTarea(NODO *TareasPendientes,NODO *TareasRealizadas);
void liberarMemoria(NODO ** Lista, int cantidad);

void main(){

    int Opcion=0, OpcionMostrar, ID=0;
 
    NODO * ListaTareas, *ListaTPendientes, *ListaTRealizadas; // ListaTareas : lista general de tareas

    ListaTareas = CrearLista();
    ListaTPendientes=CrearLista();
    ListaTRealizadas=CrearLista();
    
    while (Opcion!=5)
    {   
        printf("Ingrese una opcion para continuar:\n");
        printf("1-Cargar Lista de tareas\n2-Controlar tareas\n3-Buscar tarea\n4-Mostrar tareas\n5-Salir\n");
            fflush(stdin);
            scanf("%d",&Opcion);

        switch (Opcion)
        {
            case 1:
                CargarTareas(&ListaTareas,&ID);
                break;
            case 2:
                ControlTareas(&ListaTareas,&ListaTPendientes,&ListaTRealizadas,ContarTareas(ListaTareas));
                break;
            case 3:
                buscarTarea(ListaTPendientes,ListaTRealizadas);
                break;
            case 4:
                printf("Mostrar:\n1-Tareas pendientes:\n2-Tareas realizadas\n");
                    fflush(stdin);
                    scanf("%d",&OpcionMostrar);

                switch (OpcionMostrar)
                {
                    case 1:
                        MostrarTareas(ListaTPendientes);
                        break;
                    case 2:
                        MostrarTareas(ListaTRealizadas);
                        break;
                }
                break;
            case 5:
                liberarMemoria(&ListaTPendientes,ContarTareas(ListaTPendientes));
                liberarMemoria(&ListaTRealizadas,ContarTareas(ListaTRealizadas));
                printf("****Finalizo la ejecucion del programa *****\n");
                break; 
        }
    }   
}

//Definicion de funciones

NODO * CrearLista(){
    return NULL;
}

void InsertarNodoListaGeneral(NODO ** Lista, int ID, char *Descripcion, int Duracion){
    NODO * NuevoNodo = malloc(sizeof(NODO));
    NuevoNodo->T.TareaID=ID;
    NuevoNodo->T.Descripcion=malloc(sizeof(char)*100);
    strcpy(NuevoNodo->T.Descripcion,Descripcion);
    NuevoNodo->T.Duracion=Duracion;
    NuevoNodo->Siguiente = (*Lista);
    (*Lista)= NuevoNodo;
}

void InsertarNodoListaParticular(NODO ** Lista, NODO * NodoAux){
    NODO * NuevoNodo = NodoAux;
    NuevoNodo->Siguiente = (*Lista);
    (*Lista)= NuevoNodo;
}

NODO * AislarNodo(NODO ** Lista){
    NODO * Aux = (*Lista);
    (*Lista)=(*Lista)->Siguiente;
    Aux->Siguiente=NULL;
    return Aux;
}

void CargarTareas(NODO ** Lista, int * ID){
    int Opcion=1, Duracion;
    char *DescripcionAux;
    printf("***** CARGUE TODAS SUS TAREAS A REALIZAR *****\n");
    while (Opcion==1)
    {
        printf("Desea agregar una nueva Tarea:\n-1:SI\n-2:Finalizar Carga\n");
            fflush(stdin);
            scanf("%d", &Opcion);
        
        if(Opcion==1){
            (*ID)++;
            DescripcionAux = malloc(sizeof(char)*100);
            printf("-Descripcion:");
                fflush(stdin);
                gets(DescripcionAux);
            printf("-Duracion:");
                fflush(stdin);
                scanf("%d",&Duracion);
            InsertarNodoListaGeneral(Lista,*ID,DescripcionAux,Duracion);
            free(DescripcionAux);
            printf("\n");
        }
    }
    printf("* _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ *\n");
}

int ContarTareas(NODO * Lista){
    int cant=0;
    while (Lista!=NULL)
    {
        cant++;
        Lista=Lista->Siguiente;
    }
    return cant;
}

void ControlTareas(NODO ** Lista, NODO ** ListaTP , NODO ** ListaTR, int cantidadTareas){
    int Opcion;
    printf("***** CONTROL DE TAREAS *****\n");
    if (cantidadTareas==0)
    {
        printf("No hay tareas para controlar\n");
    }else
    {
        for (int i = 0; i < cantidadTareas; i++)
        {
            printf("-TareaID:%d\n",(*Lista)->T.TareaID);
            printf("-Descripcion:%s\n",(*Lista)->T.Descripcion);
            printf("Marcar como realizada: [1:SI || 2:NO ] :");
                fflush(stdin);
                scanf("%d",&Opcion);
            
            switch (Opcion)
            {
                case 1:
                    InsertarNodoListaParticular(ListaTR,AislarNodo(Lista));
                    break;
                case 2:
                    InsertarNodoListaParticular(ListaTP,AislarNodo(Lista));
                    break;
            }
        }
    }
}

void MostrarTareas(NODO * Lista){
    if (Lista==NULL)
    {
        printf("***** LISTA VACIA *****\n");
    }else
    {
        while (Lista!=NULL)
        {
            printf("-Tarea ID:%d\n",Lista->T.TareaID);
            printf("-Descripcion:%s\n",Lista->T.Descripcion);
            printf("-Duracion:%d\n",Lista->T.Duracion);
            Lista=Lista->Siguiente;
        }
    }         
     printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
}

NODO * BuscarXid(NODO * ListaTP, NODO * ListaTR, int ID){
    NODO *NodoAux;
    while ((ListaTP!=NULL || ListaTR!=NULL))
    {
        if (ListaTP->T.TareaID==ID)
        {
            return ListaTP;
        }else
        {
            if (ListaTR->T.TareaID==ID)
            {
                return ListaTR;
            }
        }
        ListaTP=ListaTP->Siguiente;
        ListaTR=ListaTR->Siguiente;
    }
    return NULL;
}
NODO * Buscar_X_PalabraClave(NODO * ListaTP, NODO * ListaTR, char * Descripcion){

    while ((ListaTP!=NULL || ListaTR!=NULL))
    {
        if (strstr(ListaTP->T.Descripcion,Descripcion)!=NULL)
        {
                return ListaTP;   
        }else
        {
            if (strstr(ListaTR->T.Descripcion,Descripcion)!=NULL)
            {
                return ListaTR;
            }
        }
        ListaTP=ListaTP->Siguiente;
        ListaTR=ListaTR->Siguiente;
    }

    return NULL;
}

void buscarTarea(NODO *TareasPendientes,NODO *TareasRealizadas){
    int opcion, id, flag=1;
    char *Auxarreglo;
    NODO *aux;
    while (flag==1)
    {
        printf("***** BUSQUEDA DE TAREAS *****\n");
        printf("Ingrese opcion:\n1-Busqueda por ID:\n2-Busqueda por palabra clave:\n3-Salir\n");
        fflush(stdin);
        scanf("%d", &opcion);
        
    switch (opcion)
    {
        case 1:
            printf("Ingrese el ID:");
                fflush(stdin);
                scanf("%d", &id);
                aux = BuscarXid(TareasPendientes,TareasRealizadas,id);
                if (aux != NULL)
                {
                    printf("-Tarea ID:%d\n", aux->T.TareaID);
                    printf("-Duracion:%d\n", aux->T.Duracion);
                    printf("-Descripcion:%s\n", aux->T.Descripcion);
                    printf("\n");
                }else
                {
                    printf("No se encontro tarea\n");
                } 
            break;
        case 2 :
                Auxarreglo=malloc(sizeof(char)*50);
                printf("Ingrese la palabra clave:");
                    fflush(stdin);
                    gets(Auxarreglo);
                aux = Buscar_X_PalabraClave(TareasPendientes,TareasRealizadas,Auxarreglo);
                free(Auxarreglo);
                if (aux != NULL)
                {
                    printf("-Tarea ID:%d\n", aux->T.TareaID);
                    printf("-Duracion:%d\n", aux->T.Duracion);
                    printf("-Descripcion:%s\n", aux->T.Descripcion);
                    printf("\n");
                }else
                {
                    printf("No se encontro tarea\n");
                } 
            break;
        case 3 :
            flag = 0;
            break;
        }
    }
    printf("* _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ *\n");
}

void liberarMemoria(NODO ** Lista, int cantidad){
    NODO * NodoAux;
    for (int i = 0; i < cantidad; i++)
    {
        if (Lista!=NULL)
        {
            NodoAux = AislarNodo(Lista);
            free(NodoAux->T.Descripcion);
            free(NodoAux);
        }
    }  
}