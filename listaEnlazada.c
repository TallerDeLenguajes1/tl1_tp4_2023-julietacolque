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
Lista insertarTarea(Lista lista, struct Nodo *nodo);
void listarTareas(Lista listadoTareas);
void controlTareas(Lista *TPendientes, Lista *TRealizadas, int longitud);
Tarea *buscarTareaId(Lista lista, int idBuscado);
Tarea *buscarTareaPorPalabra(Lista lista, char *palabra);
void eliminarTarea(struct Nodo *tarea);
void mostrarDatos(Lista lista);
void moverTareasTP5(Lista *TPendientes, Lista *TRealizadas, Lista *TProceso);
void liberarTodo(Lista *lista);
int main()
{
    srand(time(NULL));
    int longitud, opcion, salir = 1, id;
    char *palabra;
    Tarea *tareaBuscada;
    Lista TPendientes, TRealizadas, TProceso;

    TPendientes = crearListaVacia();
    TRealizadas = crearListaVacia();
    TProceso = crearListaVacia();
    while (salir != 0)
    {
        printf("\n<<<<<<MENU>>>>>>>\n");
        opcion = menu();

        switch (opcion)
        {
        case 1:
            TPendientes = agregarTarea(TPendientes);
            break;

        case 2:
            printf("\n TAREAS PENDIENTES \n");
            listarTareas(TPendientes);
            break;
        case 3:
            printf("\nTAREAS REALIZADAS\n");
            listarTareas(TRealizadas);
            break;

        case 4:
            printf("\nCONTROL DE TAREAS\n");
            longitud = longitudDListaDT(TPendientes);
            controlTareas(&TPendientes, &TRealizadas, longitud);
            break;
        case 5:
            printf("\nBUSQUEDA DE TAREAS POR ID\n");
            printf("Ingrese el id que busca: ");
            scanf("%d", &id);
            tareaBuscada = buscarTareaId(TPendientes, id);
            (tareaBuscada) ? printf("\nLa tarea buscada con id: %d \n", id), mostrarTarea(*tareaBuscada) : printf("\nNo se encontro la tarea");
            break;
        case 6:
            printf("\nBUSQUEDA DE TAREAS POR PALABRA\n");
            palabra = malloc(sizeof(char) * 100);
            printf("\nIngrese una palabra: ");
            fflush(stdin);
            gets(palabra);
            tareaBuscada = buscarTareaPorPalabra(TPendientes, palabra);
            (tareaBuscada) ? printf("\nLa tarea buscada por palabra %s \n", palabra), mostrarTarea(*tareaBuscada) : printf("\nNo se encontro la tarea");
            free(palabra);
            break;
        case 7:
            mostrarDatos(TPendientes);
            break;
        case 8:
            moverTareasTP5(&TPendientes, &TRealizadas, &TProceso);
            break;
        }

        printf("\nDesea seguir realizando operaciones? 1-SI 0-NO: ");
        scanf("%d", &salir);
    }

    liberarTodo(&TPendientes);
    liberarTodo(&TRealizadas);
    liberarTodo(&TProceso);

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
        printf("7-Mostrar datos\n");
        printf("8-Mover tareasTP5\n");
        printf("Ingrese la opcion: ");
        scanf("%d", &respuesta);

    } while (respuesta != 1 && respuesta != 2 && respuesta != 3 && respuesta != 4 && respuesta != 5 && respuesta != 6 && respuesta != 7 && respuesta != 8);

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
    printf("\n<<<<CREANDO TAREA>>>>\n");
    char *descripcion;
    Tarea nuevaTarea;
    descripcion = malloc(sizeof(char) * 100);
    nuevaTarea.TareaID = indice;
    fflush(stdin);
    printf("\nIngrese la descripcion de la tarea: ");
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

Lista insertarTarea(Lista lista, struct Nodo *nodo)
{

    nodo->Siguiente = lista;
    lista = nodo;
    return (lista);
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
    else
    {
        printf("\n No hay tareas pendientes\n\n");
    }
}
Tarea *buscarTareaId(Lista lista, int idBuscado)
{

    while (!esListaVacia(lista))
    {
        if (lista->T.TareaID == idBuscado)
        {
            return (&(lista)->T);
        }
        lista = lista->Siguiente;
    }
    return NULL;
}

Tarea *buscarTareaPorPalabra(Lista lista, char *palabra)
{

    while (!esListaVacia(lista))
    {
        if (strstr(lista->T.Descripcion, palabra))
        {
            return (&(lista)->T);
        }

        lista = lista->Siguiente;
    }

    return NULL;
}

void eliminarTarea(struct Nodo *tarea)
{
    free(tarea->T.Descripcion);
    free(tarea);
}

void mostrarDatos(Lista lista)
{
    if (!esListaVacia(lista))
    {
        int longitud = longitudDListaDT(lista), sumaDuracion = 0;
        for (int i = 0; i < longitud; i++)
        {
            sumaDuracion += lista->T.Duracion;
            lista = lista->Siguiente;
        }
        printf("La longitud de la lista es: %d \n", longitud);
        printf("El tiempo que tomara realizar las tareas es: %d minutos \n", sumaDuracion);
    }
    else
    {
        printf("\nLa lista esta vacia.\n");
    }
}

void moverTareasTP5(Lista *TPendientes, Lista *TRealizadas, Lista *TProceso)
{
    int id, lugarDTarea, opcionLugar, accion, salir = 1;
    struct Nodo *tarea;

    while (salir != 0)
    {
        printf("\n>>>>>LISTADO TAREAS PENDIENTES>>>>>>\n");
        listarTareas(*TPendientes);
        printf("\n>>>>>LISTADO TAREAS EN PROCESO >>>>>>\n");
        listarTareas(*TProceso);
        printf("\n>>>>>LISTADO TAREAS REALIZADAS>>>>>>\n");
        listarTareas(*TRealizadas);

        printf("Ingrese el id de la tarea que desea seleccionar: ");
        scanf("%d", &id);
        do
        {
            printf("\n1-Tareas Pendientes\n2-Tareas Realizadas\n3-Tareas en Proceso\nLa tarea se encuentra en: ");
            scanf("%d", &lugarDTarea);
        } while (lugarDTarea != 1 && lugarDTarea != 2 && lugarDTarea != 3);

        do
        {
            printf("\n1-Mover tarea\n2-Eliminar Tarea\n3-Nada\nQue desea hacer con la tarea?: ");
            scanf("%d", &accion);
        } while (accion != 1 && accion != 2 && accion != 3);

        if (accion != 3)
        {
            switch (lugarDTarea)
            {
            case 1:
                tarea = quitarNodo(TPendientes, id);
                break;
            case 2:
                tarea = quitarNodo(TRealizadas, id);
                break;
            case 3:
                tarea = quitarNodo(TProceso, id);
                break;
            }
        }

        switch (accion)
        {
        case 1:
            do
            {
                printf("\n1-TareasPendientes\n2-TareasRealizadas\n3-Tareas en Proceso\nA donde quiere mover la tarea?: ");
                scanf("%d", &opcionLugar);
            } while (lugarDTarea == opcionLugar);
            if (opcionLugar == 1)
            {
                *TPendientes = insertarTarea(*TPendientes, tarea);
            }
            if (opcionLugar == 2)
            {
                *TRealizadas = insertarTarea(*TRealizadas, tarea);
            }
            if (opcionLugar == 3)
            {
                *TProceso = insertarTarea(*TProceso, tarea);
            }

            break;
        case 2:
            printf("\n\nELIMINANDO TAREA \n\n");
            eliminarTarea(tarea);
            break;
        case 3:
            printf("\nhaciendo nada...\n");
            break;
        }

        printf("\nQuiere seguir realizando acciones 0-NO: ");
        scanf("%d", &salir);
    }

    printf("\n>>>>>LISTADO TAREAS PENDIENTES>>>>>>\n");
    listarTareas(*TPendientes);
    mostrarDatos(*TPendientes);
    printf("\n>>>>>LISTADO TAREAS EN PROCESO >>>>>>\n");
    listarTareas(*TProceso);
    mostrarDatos(*TProceso);
    printf("\n>>>>>LISTADO TAREAS REALIZADAS>>>>>>\n");
    listarTareas(*TRealizadas);
    mostrarDatos(*TRealizadas);
}

void liberarTodo(Lista *lista)
{

    int longitud = longitudDListaDT(*lista);
    for (int i = 0; i < longitud; i++)
    {
        struct Nodo *tarea = quitarNodo(lista,(*(lista))->T.TareaID);
        eliminarTarea(tarea);
    }
}