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

void inicializarNull(Tarea **tareas, int cantTareas);
void mostrarUnaTarea(Tarea **tarea, int i);
void cargarTareas(Tarea **tareas, int cantTareas);
int controlTareas(Tarea **tareas, int cantTareas, Tarea **tareasRealizadas);
void listarTareasRealizadas(Tarea **TRealizadas, int cantTRealizadas);
void listarTareasPendientes(Tarea **tareas, int cantTareas);
Tarea *buscarTarea(Tarea **tareas, int cantTareas, Tarea **tRealizadas, int cantTRealizadas, char *palabra);
int main()
{
    int cantTareas, opcion, cantTRealizadas;
    char *palabra = (char *)malloc(sizeof(char) * 50);
    Tarea *tarea;
    printf("Ingrese la cantidad de tareas: ");
    scanf("%d", &cantTareas);
    fflush(stdin);
    Tarea **tareas = (Tarea **)malloc(sizeof(Tarea *) * cantTareas);
    Tarea **tRealizadas = (Tarea **)malloc(sizeof(Tarea *) * cantTareas);

    cargarTareas(tareas, cantTareas);
    cantTRealizadas = controlTareas(tareas, cantTareas, tRealizadas);
    listarTareasRealizadas(tRealizadas, cantTRealizadas);
    listarTareasPendientes(tareas, cantTareas);

    printf("\nIngrese la palabra a buscar: ");
    fflush(stdin);
    gets(palabra);
    tarea = buscarTarea(tareas, cantTareas, tRealizadas, cantTRealizadas, palabra);

    if (tarea == NULL)
    {
        printf("\nNo se encontro coincidencias");
    }
    else
    {
        printf("\nTarea buscada por palabra ");
        printf("\nID: %d", tarea->TareaID);
        printf("\nDescripcion: %s", tarea->Descripcion);
        printf("\nDuracion: %d", tarea->Duracion);
    }
}
//---------------------FUNCIONES----------------

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

            // tareasRealizadas[cantTRealizada] = (Tarea *) malloc(sizeof(Tarea));
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

Tarea *buscarTarea(Tarea **tareas, int cantTareas, Tarea **tRealizadas, int cantTRealizadas, char *palabra)
{
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareas[i] != NULL)
        {
            if (strstr(tareas[i]->Descripcion, palabra))
            {
                return tareas[i];
            }
            else
            {
                return NULL;
            }
        }
    }

    for (int j = 0; j < cantTareas; j++)
    {
        if (strstr(tRealizadas[j]->Descripcion, palabra))
        {
            return tRealizadas[j];
        }
        else
        {
            return NULL;
        }
    }
}
