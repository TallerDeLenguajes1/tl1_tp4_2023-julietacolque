#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct Tarea
{
    int TareaID;       // Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} typedef Tarea;

struct Nodo
{

    struct Tarea T;
    struct Nodo *Siguiente;

} typedef *Lista;

int menu();
int esListaVacia(Lista L);
int longitudDListaDT(Lista L);
Tarea crearTarea(int indice);
void mostrarTarea(Tarea T);
Lista crearListaVacia();
struct Nodo *crearNodo(Lista listaTareas, int indice);
struct Nodo *quitarNodo(Lista *lista, int indice);
Lista agregarTarea(Lista TPendientes);
Lista insertarTarea(Lista TRealizadas, struct Nodo *nodo);
void listarTareas(Lista listadoTareas);
void controlTareas(Lista *TPendientes, Lista *TRealizadas, int longitud);
Tarea *buscarTareaId(Lista TPendientes, Lista TRealizadas, int idBuscado);
Tarea *buscarTareaPorPalabra(Lista TPendientes, Lista TRealizadas, char *palabra);
int main()
{
    srand(time(NULL));
    int longitud, opcion, salir = 1, id;
    char *palabra;
    Tarea *tareaBuscada;
    Lista TPendientes, TRealizadas;

    TPendientes = crearListaVacia();
    TRealizadas = crearListaVacia();
    while (salir != 0)
    {
        printf("\n\n");
        opcion = menu();

        switch (opcion)
        {
        case 1:
            TPendientes = agregarTarea(TPendientes);
            break;

        case 2:
            printf("\n\n TAREAS PENDIENTES \n\n");
            listarTareas(TPendientes);
            break;
        case 3:
            printf("\n\n TAREAS REALIZADAS \n\n");
            listarTareas(TRealizadas);
            break;

        case 4:
            printf("\n\n CONTROL DE TAREAS \n\n");
            longitud = longitudDListaDT(TPendientes);
            controlTareas(&TPendientes, &TRealizadas, longitud);
            break;
        case 5:
            printf("\n\n BUSQUEDA DE TAREAS POR ID \n\n");
            printf("Ingrese el id que busca: ");
            scanf("%d", &id);
            tareaBuscada = buscarTareaId(TPendientes, TRealizadas, id);
            (tareaBuscada) ? printf("\nLa tarea buscada con id: %d \n", id), mostrarTarea(*tareaBuscada) : printf("\nNo se encontro la tarea");
            break;
        case 6:
            printf("\n\n BUSQUEDA DE TAREAS POR PALABRA \n\n");
            palabra = malloc(sizeof(char) * 100);
            printf("\nIngrese una palabra: ");
            fflush(stdin);
            gets(palabra);
            tareaBuscada = buscarTareaPorPalabra(TPendientes, TRealizadas, palabra);
            (tareaBuscada) ? printf("\nLa tarea buscada por palabra %s \n", palabra), mostrarTarea(*tareaBuscada) : printf("\nNo se encontro la tarea");
            break;
        }
        printf("\n\nDesea seguir realizando operaciones? 1-SI 0-NO: ");
        scanf("%d", &salir);
    }

    return 0;
}

int menu()
{
    int respuesta;
    do
    {
        printf("\n1-Cargar tarea");
        printf("\n2-Listar tareas Pendientes\n");
        printf("3-Listar tareas Realizadas\n");
        printf("4-Control de tareas\n");
        printf("5-Busqueda de tareas por ID\n");
        printf("6-Busqueda de tareas por Palabra\n");
        printf("Ingrese la opcion: ");
        scanf("%d", &respuesta);
        printf("\n\n");

    } while (respuesta != 1 && respuesta != 2 && respuesta != 3 && respuesta != 4 && respuesta != 5 && respuesta != 6);

    return respuesta;
}

int esListaVacia(Lista L)
{
    if (L == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int longitudDListaDT(Lista L)
{
    int cantidad = 0;
    while (!esListaVacia(L))
    {
        L = L->Siguiente;
        cantidad++;
    }
    return cantidad;
}
Tarea crearTarea(int indice)
{
    char *descripcion;
    Tarea nuevaTarea;
    descripcion = malloc(sizeof(char) * 100);
    nuevaTarea.TareaID = indice;
    fflush(stdin);
    printf("Ingrese la descripcion de la tarea: ");
    gets(descripcion);
    nuevaTarea.Descripcion = malloc(sizeof(char) * 100);
    strcpy(nuevaTarea.Descripcion, descripcion);
    free(descripcion);
    nuevaTarea.Duracion = 10 + rand() % 91;
    return (nuevaTarea);
}

void mostrarTarea(Tarea T)
{
    printf("\n--------   Tarea N %d   ----------\n", T.TareaID);
    printf("ID: %d \n", T.TareaID);
    printf("DESCRIPCION: %s \n", T.Descripcion);
    printf("DURACION: %d \n", T.Duracion);
}

Lista crearListaVacia()
{
    return NULL;
}

struct Nodo *crearNodo(Lista TPendientes, int indice)
{
    struct Nodo *nuevoNodo;
    nuevoNodo = (struct Nodo *)malloc(sizeof(struct Nodo));
    nuevoNodo->T = crearTarea(indice);
    nuevoNodo->Siguiente = TPendientes;
    return (nuevoNodo);
}

struct Nodo *quitarNodo(Lista *lista, int indice)
{

    struct Nodo *aux = *lista;
    struct Nodo *auxAnterior = *lista;
    int bandera = 0;
    while (!esListaVacia(aux) && aux->T.TareaID != indice)
    {
        auxAnterior = aux;
        aux = aux->Siguiente;
        bandera = 1;
    }
    // mi error era que no estaba pasando por referencia la lista asi se guardaban los cambios. entonces debia pasarla como puntero asi los cambios permanecian y podia retornar el nodo. como es un doble puntero entonces solo debia colocar & en la llamda de la funcion.
    //  puede pasar q llego a null o sea no encontro el indice o si lo hizo.

    // 1 caso seria que la tarea uno deba ser quitada

    if (aux)
    { // aqui nos aseguramos que se encontro el nodo.

        if (bandera == 0)
        { // caso del nodo 1
            *lista = (*(lista))->Siguiente;
        }
        else
        {
            auxAnterior->Siguiente = aux->Siguiente;
        }
        aux->Siguiente = NULL;
    }

    return (aux);
}

Lista agregarTarea(Lista TPendientes)
{

    TPendientes = crearNodo(TPendientes, longitudDListaDT(TPendientes) + 1);
    return (TPendientes);
}

Lista insertarTarea(Lista TRealizadas, struct Nodo *nodo)
{

    nodo->Siguiente = TRealizadas;
    TRealizadas = nodo;
    return (TRealizadas);
}

void listarTareas(Lista listadoTareas)
{

    if (!esListaVacia(listadoTareas))
    {
        int longitud = longitudDListaDT(listadoTareas);
        for (int i = 0; i < longitud; i++)
        {
            mostrarTarea(listadoTareas->T);
            listadoTareas = listadoTareas->Siguiente;
        }
    }
    else
    {
        printf("\nNo hay tareas para mostrar\n");
    }
}

void controlTareas(Lista *TPendientes, Lista *TRealizadas, int longitud)
{
    if (*TPendientes)
    {
        int respuesta;
        struct Nodo *auxiliar = *TPendientes;

        for (int i = 0; i < longitud; i++)
        {
            mostrarTarea(auxiliar->T);

            do
            {
                printf("Realizo la tarea 1-Si 0-No: ");
                scanf("%d", &respuesta);
            } while (respuesta != 1 && respuesta != 0);

            if (respuesta == 1)
            {
                struct Nodo *nodoAquitar;
                nodoAquitar = quitarNodo(TPendientes, auxiliar->T.TareaID);
                *TRealizadas = insertarTarea(*TRealizadas, nodoAquitar);
                auxiliar = (*(TPendientes));
            }
            else
            {
                auxiliar = (*(TPendientes))->Siguiente;
            }
        }
        // aux perdio la linea de la lista de tareas por ello se produjo un error de segmentacion porque una vezz que quite el primer nodo se perdio la conexion con el resto pero Tpendientes mantiene la conexion porque la funcion quitar nodo la conserva gracias a la modificacion que se le hace, por lo tanto, cuando a aux le redirecciono que apunte al nodo 2 ya lo recorre sin problema
    }
      else {
            printf("\n No hay tareas pendientes\n\n");
        }
}
Tarea *buscarTareaId(Lista TPendientes, Lista TRealizadas, int idBuscado)
{

    while (!esListaVacia(TPendientes) && TPendientes->T.TareaID != idBuscado)
    {
        TPendientes = TPendientes->Siguiente;
    }
    if (TPendientes)
    {
        return (&(TPendientes)->T);
    }

    while (!esListaVacia(TRealizadas) && TRealizadas->T.TareaID != idBuscado)
    {
        TRealizadas = TRealizadas->Siguiente;
    }
    if (TRealizadas)
    {
        return (&(TRealizadas)->T);
    }
    return NULL;
}

Tarea *buscarTareaPorPalabra(Lista TPendientes, Lista TRealizadas, char *palabra)
{

    while (!esListaVacia(TPendientes))
    {
        if (strstr(TPendientes->T.Descripcion, palabra))
        {
            return (&(TPendientes)->T);
        }

        TPendientes = TPendientes->Siguiente;
    }
    while (!esListaVacia(TRealizadas))
    {
        if (strstr(TRealizadas->T.Descripcion, palabra))
        {
            return (&(TRealizadas)->T);
        }

        TRealizadas = TRealizadas->Siguiente;
    }

    return NULL;
}