#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

struct Tarea
{
    int TareaID; // Numerado en ciclo iterativo
    char *Descripcion;
    int Duracion; // entre 10 – 100
} typedef Tarea;

void MostrartareaBuscada(Tarea *tarea);
int menu();
void inicializarNull(Tarea **tareas, int cantTareas);
void mostrarUnaTarea(Tarea **tarea, int i);
void cargarTareas(Tarea **tareas, int cantTareas);
int controlTareas(Tarea **tareas, int cantTareas, Tarea **tareasRealizadas);
void listarTareasRealizadas(Tarea **TRealizadas, int cantTRealizadas);
void listarTareasPendientes(Tarea **tareas, int cantTareas);
Tarea *buscarTareaID(Tarea **tareas, Tarea **TRealizadas, int cantTareas, int cantTRealizadas, int id);
Tarea *buscarTareaPalabra(Tarea **tareas, int cantTareas, Tarea **tRealizadas, int cantTRealizadas, char *palabra);

int main()
{
    int cantTareas, cantTRealizadas, idBuscado, opcion;
    Tarea *tareaBuscadaId, *tareaPalabra;
    char *palabra = (char *)malloc(sizeof(char) * 50);

    printf("Ingrese la cantidad de tareas: ");
    scanf("%d", &cantTareas);
    fflush(stdin);

    Tarea **tareas = (Tarea **)malloc(sizeof(Tarea *) * cantTareas);
    Tarea **tRealizadas = (Tarea **)malloc(sizeof(Tarea *) * cantTareas);

    inicializarNull(tareas, cantTareas);
    inicializarNull(tRealizadas, cantTareas);

    cargarTareas(tareas, cantTareas);

    cantTRealizadas = controlTareas(tareas, cantTareas, tRealizadas);

    opcion = menu();

    switch (opcion)
    {
    case 1:
        printf("\nIngrese la palabra a buscar: ");
        fflush(stdin);
        gets(palabra);
        tareaPalabra = buscarTareaPalabra(tareas, cantTareas, tRealizadas, cantTRealizadas, palabra);
        (tareaPalabra == NULL) ? printf("\nNo se encontro coincidencias") : MostrartareaBuscada(tareaPalabra);
        break;
    case 2:
        printf("\nIngrese el id de la tarea: ");
        scanf("%d", &idBuscado);
        tareaBuscadaId = buscarTareaID(tareas, tRealizadas, cantTareas, cantTRealizadas, idBuscado);
        (tareaBuscadaId == NULL) ? printf("\nNo se encontro coincidencias") : MostrartareaBuscada(tareaBuscadaId);
        break;
    case 3:
        listarTareasRealizadas(tRealizadas, cantTRealizadas);
        break;
    case 4:
        listarTareasPendientes(tareas, cantTareas);
        break;
    }
}
//---------------------FUNCIONES----------------

void MostrartareaBuscada(Tarea *tarea)
{
    printf("\n---------La tarea buscada ---------\n");
    printf("\nID: %d", tarea->TareaID);
    printf("\nDescripcion: %s", tarea->Descripcion);
    printf("\nDuracion: %d", tarea->Duracion);
}
int menu()
{
    int valor;
    do
    {
        printf("\n1-Buscar tarea por palabra");
        printf("\n2-Buscar tarea por ID");
        printf("\n3-Listar tareas Realizadas");
        printf("\n4-Listar tareas pendientes");
        printf("\nIngrese la opcion: ");
        scanf("%d", &valor);
    } while (valor != 1 && valor != 2 && valor != 3 && valor != 4);
    return valor;
}
void inicializarNull(Tarea **tareas, int cantTareas)
{
    // inicializar en null
    for (int i = 0; i < cantTareas; i++)
    {
        tareas[i] = NULL;
    }
}
void mostrarUnaTarea(Tarea **tarea, int i)
{
    printf("\n-----TAREA %d-----\n", tarea[i]->TareaID);
    printf("Id: %d\n", tarea[i]->TareaID);
    printf("Descripcion: %s \n", tarea[i]->Descripcion);
    printf("Duracion: %d \n", tarea[i]->Duracion);
}

void cargarUnaTarea(Tarea **tarea, int i)
{
    srand(time(NULL));
    char *buff;

    buff = (char *)malloc(sizeof(char) * 100);
    // reservar dinamicamente memoria para cada tarea.
    tarea[i] = (Tarea *)malloc(sizeof(Tarea));
    tarea[i]->TareaID = i + 1;
    printf("Tarea descripcion:");
    fflush(stdin);
    gets(buff);
    tarea[i]->Descripcion = malloc(sizeof(char) * (strlen(buff) + 1));
    strcpy(tarea[i]->Descripcion, buff);
    tarea[i]->Duracion = 10 + rand() % 91;

    free(buff);
}

void cargarTareas(Tarea **tareas, int cantTareas)
{

    for (int i = 0; i < cantTareas; i++)
    {
        cargarUnaTarea(tareas, i);
    }
}

int controlTareas(Tarea **tareas, int cantTareas, Tarea **tareasRealizadas)
{
    int valor, cantTRealizada = 0;
    for (int i = 0; i < cantTareas; i++)
    {
        mostrarUnaTarea(tareas, i);

        do
        {
            printf("Realizo la tarea 1-Si 0-No : ");
            scanf("%d", &valor);
        } while (valor != 1 && valor != 0);

        if (valor == 1)
        {

            tareasRealizadas[cantTRealizada] = (Tarea *)malloc(sizeof(Tarea));
            tareasRealizadas[cantTRealizada] = tareas[i];
            cantTRealizada++;
            tareas[i] = NULL;
        };
    }
    return cantTRealizada;
}

void listarTareasRealizadas(Tarea **TRealizadas, int cantTRealizadas)
{

    printf("\n_____________Tareas REALIZADAS__________\n");
    for (int i = 0; i < cantTRealizadas; i++)
    {
        mostrarUnaTarea(TRealizadas, i);
    }
}

void listarTareasPendientes(Tarea **tareas, int cantTareas)

{

    printf("\n_____________Tareas PENDIENTES__________\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareas[i] != NULL)
        {
            mostrarUnaTarea(tareas, i);
        }
    }
}

Tarea *buscarTareaPalabra(Tarea **tareas, int cantTareas, Tarea **tRealizadas, int cantTRealizadas, char *palabra)
{

    for (int i = 0; i < cantTareas; i++)
    {
        if (tareas[i] != NULL)
        {

            if (strstr(tareas[i]->Descripcion, palabra))
            {
                return tareas[i];
            }
        }
    }

    for (int j = 0; j < cantTareas; j++)
    {
        if (strstr(tRealizadas[j]->Descripcion, palabra))
        {
            return tRealizadas[j];
        }
    }
    return NULL;
}

Tarea *buscarTareaID(Tarea **tareas, Tarea **TRealizadas, int cantTareas, int cantTRealizadas, int id)
{

    for (int i = 0; i < cantTRealizadas; i++)
    {
        if (tareas[i] != NULL)
        {
            if (tareas[i]->TareaID == id)
            {
                return tareas[i];
            }
        }
    }

    for (int j = 0; j < cantTRealizadas; j++)
    {
        if (TRealizadas[j]->TareaID == id)
        {

            return TRealizadas[j];
        }
    }
    return NULL;
}
