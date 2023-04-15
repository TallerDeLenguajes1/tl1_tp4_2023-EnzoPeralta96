#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Tarea{
    int TareaID;
    char *Descripcion;
    int Duracion;
}typedef Tarea;

Tarea** crearArreglo(int cantidad);//crea arreglo de punteros dinamicos
void inicializarArreglo(Tarea **arreglo, int cantidad);
void cargarTarea(Tarea **arregloTareas, int cantidad);
void controlTareas(Tarea **tareasPendientes, Tarea **tareaRealizada, int cantidad);
void listarTareas(Tarea **TareasPendientes, Tarea ** TareasRealizadas, int cantidad);
Tarea * buscarTareaxID(Tarea **TareasPendientes,Tarea **TareasRealizadas, int cantidad, int ID);
Tarea * buscarTareaxPalabraClave(Tarea **TareasPendientes,Tarea **TareasRealizadas, int cantidad, char palabraClave[]);
void buscarTarea(Tarea **TareasPendientes,Tarea **TareasRealizadas, int cantidad);
void liberarMemoria(Tarea **TareasPendientes, Tarea ** TareasRealizadas, int cantidad);

void main(){
    int cantidadTareas;
    printf("Ingrese la cantidad de tareas a realizar");
        fflush(stdin);
        scanf("%d", &cantidadTareas);

    Tarea **listadoTareas = crearArreglo(cantidadTareas);
    Tarea **tareasRealizadas = crearArreglo(cantidadTareas);

    inicializarArreglo(listadoTareas,cantidadTareas);
    inicializarArreglo(tareasRealizadas,cantidadTareas);
    cargarTarea(listadoTareas,cantidadTareas);
    controlTareas(listadoTareas,tareasRealizadas,cantidadTareas);
    listarTareas(listadoTareas,tareasRealizadas,cantidadTareas);
    buscarTarea(listadoTareas,tareasRealizadas,cantidadTareas);
    liberarMemoria(listadoTareas,tareasRealizadas,cantidadTareas);


    for (int i = 0; i < cantidadTareas; i++)
    {
        printf("primer for ");
        printf("id:%d ",listadoTareas[i]->TareaID);
        printf("descrip:%s\n", listadoTareas[i]->Descripcion);
    }
      for (int i = 0; i < cantidadTareas; i++)
    {
        printf("id:%d ",tareasRealizadas[i]->TareaID);
        printf("descrip:%s\n", tareasRealizadas[i]->Descripcion);
    }
    
}

Tarea** crearArreglo(int cantidad){
    Tarea **arregloAux=malloc(sizeof(Tarea *)*cantidad);
    return arregloAux;
}

void inicializarArreglo(Tarea **arreglo, int cantidad){
    for (int i = 0; i < cantidad; i++)
    {
        arreglo[i]=NULL;
    }
}

void cargarTarea(Tarea **arregloTareas, int cantidad){
    char *descripcionAux;
    printf("Ingrese las tareas a realizar\n");
    for ( int i=0 ; i < cantidad; i++)
    {
        arregloTareas[i]=(Tarea *)malloc(sizeof(Tarea));
        printf("***** Tarea Nro:%d *****\n",i+1);
        arregloTareas[i]->TareaID=i+1;

        descripcionAux = (char *)malloc(sizeof(char)*100);
        printf("Descripcion tarea:");
        fflush(stdin);
        gets(descripcionAux);
        arregloTareas[i]->Descripcion=(char *)malloc(sizeof(char)*(strlen(descripcionAux)+1));
        strcpy(arregloTareas[i]->Descripcion,descripcionAux);

        printf("Duracion:");
            scanf("%d",&arregloTareas[i]->Duracion);

        free(descripcionAux);
    }
    puts("* ------------------------------------- *\n");
}

void controlTareas(Tarea **tareasPendientes, Tarea **tareaRealizada, int cantidad){
    printf("****** Control De Tareas ******\n");
    int control;
    for (int i = 0; i < cantidad; i++)
    {
        printf("-Tarea ID:%d \n", tareasPendientes[i]->TareaID,tareasPendientes[i]->Duracion);
        printf("-Descripcion:%s\n",tareasPendientes[i]->Descripcion);
        printf("Tarea realizada:\n -Opcion 1:SI\n -Opcion 0 :NO");
            fflush(stdin);
            scanf("%d",&control);
        
        if (control==1)
        {
            //tareaRealizada[i]=malloc(sizeof(Tarea)); no hace falta porque solo paso la direccion de memoria
            tareaRealizada[i]=tareasPendientes[i];
            tareasPendientes[i]=NULL;
            printf("Tarea ID:%d guarda como realizada\n", tareaRealizada[i]->TareaID);
        }
        printf("\n");
    }
    puts("* ------------------------------------- *\n");
}

void listarTareas(Tarea **TareasPendientes, Tarea ** TareasRealizadas, int cantidad){
    puts("***** Tarea realizadas ****\n");
    for (int i = 0; i < cantidad; i++)
    {
        if (TareasRealizadas[i]!=NULL)
        {
            printf("Tarea ID:%d || Duracion:%d\n", TareasRealizadas[i]->TareaID, TareasRealizadas[i]->Duracion);
            printf("Descripcion:%s\n", TareasRealizadas[i]->Descripcion);
        }
    }
    puts("* ------------------------------------- *\n");
    printf("****** Tareas Pendientes *****\n");
    for (int j = 0; j < cantidad; j++)
    {
        if (TareasPendientes[j]!=NULL)
        {
            printf("Tarea pendiente ID:%d\n", TareasPendientes[j]->TareaID);
        }   
    }
     puts("* ------------------------------------- *\n");
}

Tarea * buscarTareaxID(Tarea **TareasPendientes,Tarea **TareasRealizadas, int cantidad, int ID){

    for (int i = 0; i < cantidad; i++)
    {
        if (TareasPendientes[i]!=NULL && ID==TareasPendientes[i]->TareaID)
        {
            return(TareasPendientes[i]);
        }else
        {
            if (TareasRealizadas[i]!=NULL && ID==TareasRealizadas[i]->TareaID)
            {
                return(TareasRealizadas[i]);
            } 
        }
    }
    return NULL;
}

Tarea * buscarTareaxPalabraClave(Tarea **TareasPendientes,Tarea **TareasRealizadas, int cantidad, char palabraClave[]){
    for (int i = 0; i < cantidad; i++)
    {
        if (TareasPendientes[i]!=NULL && strstr(TareasPendientes[i]->Descripcion,palabraClave))
        {
            return(TareasPendientes[i]);
        }else
        {
            if (TareasRealizadas[i]!=NULL && strstr(TareasRealizadas[i]->Descripcion,palabraClave))
            {
                return(TareasRealizadas[i]);
            } 
        }
    }
    return NULL;
}

void buscarTarea(Tarea **TareasPendientes,Tarea **TareasRealizadas, int cantidad){
    int opcion, id, flag=1;
    char *Auxarreglo=malloc(sizeof(char)*50);
    Tarea *aux;
    while (flag==1)
    {
        printf("***** Busqueda de Tarea *****\n");
        printf("Ingrese opcion:\n1-Busqueda por ID:\n2-Busqueda por palabra clave:\n3-Salir\n");
        fflush(stdin);
        scanf("%d", &opcion);
    switch (opcion)
    {
        case 1:
            printf("Ingrese el ID:");
                fflush(stdin);
                scanf("%d", &id);
                aux = buscarTareaxID(TareasPendientes,TareasRealizadas,cantidad,id);
                if (aux != NULL)
                {
                    printf("-Tarea ID:%d\n", aux->TareaID);
                    printf("-Duracion:%d\n", aux->Duracion);
                    printf("-Descripcion:%s\n", aux->Descripcion);
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
                aux = buscarTareaxPalabraClave(TareasPendientes,TareasRealizadas,cantidad,Auxarreglo);
                free(Auxarreglo);
                if (aux != NULL)
                {
                    printf("-Tarea ID:%d\n", aux->TareaID);
                    printf("-Duracion:%d\n", aux->Duracion);
                    printf("-Descripcion:%s\n", aux->Descripcion);
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
}


void liberarMemoria(Tarea **TareasPendientes, Tarea ** TareasRealizadas, int cantidad){
    for (int i = 0; i < cantidad; i++)
    {
        free(TareasPendientes[i]);
        free(TareasRealizadas[i]);
    }
    free(TareasPendientes);
    free(TareasRealizadas);
    printf("Memoria liberada con exito!\n");
}


   



