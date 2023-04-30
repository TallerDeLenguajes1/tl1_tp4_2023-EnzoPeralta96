#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Tarea
{
    int TareaID;
    char * Descripcion;
    int Duracion;
}typedef Tarea;

struct Nodo
{
    Tarea * T;
    struct Nodo * siguiente;
}typedef Nodo;

Tarea * CrearTarea(int ID, char * descripcion, int duracion){
    Tarea *nueva = (Tarea *)malloc(sizeof(Tarea));
    nueva->TareaID=ID;
    nueva->Descripcion = malloc(sizeof(char)*(1+strlen(descripcion)));
    strcpy(nueva->Descripcion,descripcion);
    nueva->Duracion=duracion;
    return nueva;
}

Nodo * CrearNodo(Tarea * tarea){
    Nodo * NuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    NuevoNodo->T = tarea;
    NuevoNodo->siguiente=NULL;
    return NuevoNodo;
}

void InsertarNodo(Nodo ** Lista, Nodo * nodo){
    nodo->siguiente = (*Lista);
    (*Lista) = nodo;
}

Nodo *  CrearListaVacia(){
    return NULL;
}

void CargarLista(Nodo ** Lista){
    int Id=0, duracion, opcion=1;
    char * descripcion;
    Tarea * tareaAux;
    Nodo * nodoAux;

    while (opcion == 1)
    {
        printf("¿Desea cargar una Tarea?\n-1:SI\n-2:Finalizar Carga\n");
            fflush(stdin);
            scanf("%d",&opcion);
        
        if (opcion == 1)
        {
            Id++;
            descripcion = malloc(sizeof(char)*100);
            printf("-Descripcion:");
                fflush(stdin);
                gets(descripcion);
            printf("-Duracion:");
                fflush(stdin);
                scanf("%d",&duracion);

            tareaAux = CrearTarea(Id,descripcion,duracion);
            nodoAux = CrearNodo(tareaAux);
            InsertarNodo(Lista,nodoAux);

            free(descripcion);
        }    
    }
}

Nodo * AislarNodo(Nodo ** Lista, int id){
    Nodo * aux = *Lista;
    Nodo * auxAnt = NULL;   

    while (aux !=NULL && aux->T->TareaID!=id)
    {
        auxAnt = aux;
        aux=aux->siguiente;
    }

    if (aux!=NULL)
    {
        if (aux==(*Lista))
        {
            (*Lista)=aux->siguiente;
        }else
        {
            auxAnt->siguiente=aux->siguiente;
        }
        aux->siguiente=NULL;
       
    }
    return aux;
}



void controlTareas(Nodo ** ListaGeneral,Nodo ** ListaTPend, Nodo ** ListaTProc, Nodo ** ListaTRealizada){

    Nodo * ListaAux = (*ListaGeneral), *nodoAux; // Lista con todas las tareas cargadas - nodo para guardar un nodo quitado de la lista
    int opcion;
    while (ListaAux != NULL)
    {
        printf("-Tarea ID:%d\n",ListaAux->T->TareaID);
        printf("Descripcion:%s\n",ListaAux->T->Descripcion);
        printf("Marcar tarea como:\nOpcion 1:Pendiente\nOpcion 2:En proceso\nOpcion 3:Realizada\n");
            fflush(stdin);
            scanf("%d",&opcion);
        switch (opcion)
        {
        case 1:
            nodoAux = AislarNodo(ListaGeneral,ListaAux->T->TareaID); 
            InsertarNodo(ListaTPend,nodoAux);
            break;
        case 2:
            nodoAux = AislarNodo(ListaGeneral,ListaAux->T->TareaID);
            InsertarNodo(ListaTProc,nodoAux); 
            break;
        case 3:
            nodoAux = AislarNodo(ListaGeneral,ListaAux->T->TareaID);
            InsertarNodo(ListaTRealizada,nodoAux);
            break;
        }
        ListaAux=(*ListaGeneral);
        printf("\n");
    }
    printf("----- fin de control de listas ------\n");
}

void MostrarTareas(Nodo * Lista){
    if (Lista==NULL)
    {
        printf("***** LISTA VACIA *****\n");
    }else
    {
        while (Lista!=NULL)
        {
            printf("-Tarea ID:%d\n",Lista->T->TareaID);
            printf("-Descripcion:%s\n",Lista->T->Descripcion);
            printf("-Duracion:%d\n",Lista->T->Duracion);
            printf("\n");
            Lista=Lista->siguiente;
        }
    }         
     printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
}

void MostrarDatos(Nodo * Lista){
    int TiempoTotal=0, CantidadTareas=0;
    while (Lista!=NULL)
    {
        CantidadTareas++;
        TiempoTotal= TiempoTotal + Lista->T->Duracion;
        Lista=Lista->siguiente;
    }
    printf("Cantidad de tareas:%d\n",CantidadTareas);
    printf("Tiempo total de duracion:%d\n",TiempoTotal);    
    printf("\n");
}

void Eliminar(Nodo * nodo){
    free(nodo->T->Descripcion);
    free(nodo);
}


void LiberarMemoria(Nodo ** Lista){

    Nodo * NodoAux=NULL;

    while ((*Lista)!=NULL)
    {
        NodoAux = AislarNodo(Lista,(*Lista)->T->TareaID);
        free(NodoAux->T->Descripcion);
        free(NodoAux);
    }   
}
void main(){

    int flag = 1, opcion, id, opcionLista;

    Nodo *ListaTareas,*ListaPendientes, *ListaRealizadas, *ListaProceso;
    Nodo * NodoAux = NULL;

    ListaTareas=CrearListaVacia();
    ListaPendientes=CrearListaVacia();
    ListaRealizadas=CrearListaVacia();
    ListaProceso=CrearListaVacia();

    CargarLista(&ListaTareas);
    controlTareas(&ListaTareas,&ListaPendientes,&ListaProceso,&ListaRealizadas);

    while (flag==1)
    {
        printf("***** Lista de tareas PENDIENTES *****\n");
            MostrarTareas(ListaPendientes);
        printf("***** Lista de tareas EN PROCESO *****\n");
            MostrarTareas(ListaProceso);
        printf("***** Lista de tareas REALIZADAS *****\n");
            MostrarTareas(ListaRealizadas);
        
        printf("Ingrese el ID de la tarea que desea seleccionar");
            fflush(stdin);
            scanf("%d",&id);
        
        
    
        printf("Que accion desea realizar:-1:Mover Tarea\n2-Eliminar tarea\n-3:No hacer nada\n");
            fflush(stdin);
            scanf("%d", &opcion);

            if (opcion != 3)
            {
                if (NodoAux==NULL)
                {
                    NodoAux=AislarNodo(&ListaPendientes,id);

                    if (NodoAux==NULL)
                    {
                        NodoAux=AislarNodo(&ListaProceso,id);

                        if (NodoAux==NULL)
                        {
                            NodoAux=AislarNodo(&ListaRealizadas,id);
                        }
                    }
                }
            }
            

            switch (opcion)
            {
            case 1:
                printf("A que lista desea mover la tarea?\n-1:Tareas pendientes\n-2:Tareas en proceso\n-3:Tareas realizadas");
                    fflush(stdin);
                    scanf("%d",&opcionLista);

                switch (opcionLista)
                {
                case 1:
                    InsertarNodo(&ListaPendientes,NodoAux);
                    break;
                case 2:
                     InsertarNodo(&ListaProceso,NodoAux);
                    break;
                case 3:
                     InsertarNodo(&ListaRealizadas,NodoAux);
                     break;
                }
                break;
            case 2:
                Eliminar(NodoAux);
                break;
            case 3:
                break;

            }
            NodoAux = NULL;
            printf("Desea modificar otra tarea?\n1:SI\n2:NO\n");
                fflush(stdin);
                scanf("%d",&opcion);


            if (opcion!=1)
            {

                printf("***** Lista de tareas PENDIENTES *****\n");
                    MostrarTareas(ListaPendientes);
                    MostrarDatos(ListaPendientes);
                printf("\n");

                printf("***** Lista de tareas EN PROCESO *****\n");
                    MostrarTareas(ListaProceso);
                    MostrarDatos(ListaProceso);
                printf("\n");

                printf("***** Lista de tareas REALIZADAS *****\n");
                    MostrarTareas(ListaRealizadas);
                    MostrarDatos(ListaRealizadas);
                printf("\n");

                flag=0;
            }
            
    }

    LiberarMemoria(&ListaPendientes);
    LiberarMemoria(&ListaProceso);
    LiberarMemoria(&ListaRealizadas);            
    printf("Finalizo la ejecucion del programa\n");
}





