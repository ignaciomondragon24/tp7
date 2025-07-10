#include <stdio.h>
#include <string.h>
#include <float.h>  

// Constantes
#define MAX_ANALISTAS 10
#define MAX_PROYECTOS 15
#define MAX_PLANILLAS 100
#define MAX_NOMBRE 50
#define HORAS_MINIMAS 5

// Estructuras para el sistema de consultora
struct Analista {
    char nombre[MAX_NOMBRE];
    float valorHora;
    float totalHoras;
    float sueldo;
};

struct Planilla {
    int numeroAnalista;
    int numeroProyecto;
    float horasTrabajadas;
};

int main() {
    struct Analista analistas[MAX_ANALISTAS];
    struct Planilla planillas[MAX_PLANILLAS]; 
    float horasProyecto[MAX_PROYECTOS] = {0}; 
    float horasAnalistaProyecto[MAX_ANALISTAS][MAX_PROYECTOS] = {0}; 
    int numPlanillas = 0;
    
    printf("=== EJERCICIO 3: SISTEMA DE CONSULTORA ===\n");
    
    // Cargar nombres y valor hora de analistas
    for (int i = 0; i < MAX_ANALISTAS; i++) {
        printf("Ingrese nombre del analista %d: ", i + 1);
        scanf("%s", analistas[i].nombre);
        printf("Ingrese valor hora del analista %d: ", i + 1);
        scanf("%f", &analistas[i].valorHora);
        analistas[i].totalHoras = 0;
        analistas[i].sueldo = 0;
    }
    
    // Cargar planillas
    printf("\nIngrese las planillas (ingrese 0 en número de analista para terminar):\n");
    int continuar = 1;
    while (continuar) {
        printf("\nPlanilla %d:\n", numPlanillas + 1);
        printf("Número de analista (1-10, 0 para terminar): ");
        scanf("%d", &planillas[numPlanillas].numeroAnalista);
        
        if (planillas[numPlanillas].numeroAnalista == 0) {
            continuar = 0;
        }
        else if (planillas[numPlanillas].numeroAnalista < 1 || planillas[numPlanillas].numeroAnalista > MAX_ANALISTAS) {
            printf("Número de analista inválido. Debe ser entre 1 y %d.\n", MAX_ANALISTAS);
        }
        else {
            printf("Número de proyecto (1-%d): ", MAX_PROYECTOS);
            scanf("%d", &planillas[numPlanillas].numeroProyecto);
            
            if (planillas[numPlanillas].numeroProyecto < 1 || planillas[numPlanillas].numeroProyecto > MAX_PROYECTOS) {
                printf("Número de proyecto inválido. Debe ser entre 1 y %d.\n", MAX_PROYECTOS);
            }
            else {
                printf("Horas trabajadas: ");
                scanf("%f", &planillas[numPlanillas].horasTrabajadas);
                numPlanillas++;
            }
        }
    }
    
    // Procesar datos
    for (int i = 0; i < numPlanillas; i++) {
        int analista = planillas[i].numeroAnalista - 1;
        int proyecto = planillas[i].numeroProyecto - 1;
        float horas = planillas[i].horasTrabajadas;
        
        // Acumular horas totales por analista
        analistas[analista].totalHoras += horas;
        
        // Acumular horas por proyecto
        horasProyecto[proyecto] += horas;
        
        // Acumular horas por analista por proyecto
        horasAnalistaProyecto[analista][proyecto] += horas;
    }
    
    // Calcular sueldos
    for (int i = 0; i < MAX_ANALISTAS; i++) {
        analistas[i].sueldo = analistas[i].totalHoras * analistas[i].valorHora;
    }
    
    // Mostrar resultados
    printf("\n=== RESULTADOS ===\n");
    
    // a. Cantidad de hs trabajadas en total por cada analista
    printf("\na) Horas totales por analista:\n");
    for (int i = 0; i < MAX_ANALISTAS; i++) {
        printf("Analista %s: %.2f horas\n", analistas[i].nombre, analistas[i].totalHoras);
    }
    
    // b. Total de horas trabajadas por cada analista en cada proyecto
    printf("\nb) Horas por analista en cada proyecto:\n");
    for (int i = 0; i < MAX_ANALISTAS; i++) {
        printf("Analista %s:\n", analistas[i].nombre);
        for (int j = 0; j < MAX_PROYECTOS; j++) {
            if (horasAnalistaProyecto[i][j] > 0) {
                printf("  Proyecto %d: %.2f horas\n", j + 1, horasAnalistaProyecto[i][j]);
            }
        }
    }
    
    // c. Total de hs trabajadas sobre cada proyecto
    printf("\nc) Horas totales por proyecto:\n");
    for (int i = 0; i < MAX_PROYECTOS; i++) {
        if (horasProyecto[i] > 0) {
            printf("Proyecto %d: %.2f horas\n", i + 1, horasProyecto[i]);
        }
    }
    
    // d. Qué analista trabajó menos en el proyecto 1
    printf("\nd) Analista que trabajó menos en el proyecto 1:\n");
    int menorAnalista = -1;
    float menorHoras = FLT_MAX;  // Usar constante en lugar de número mágico
    for (int i = 0; i < MAX_ANALISTAS; i++) {
        if (horasAnalistaProyecto[i][0] > 0 && horasAnalistaProyecto[i][0] < menorHoras) {
            menorHoras = horasAnalistaProyecto[i][0];
            menorAnalista = i;
        }
    }
    if (menorAnalista != -1) {
        printf("Analista %s trabajó menos en proyecto 1: %.2f horas\n", 
               analistas[menorAnalista].nombre, menorHoras);
    } else {
        printf("Ningún analista trabajó en el proyecto 1\n");
    }
    
    // e. Sueldo de cada analista
    printf("\ne) Sueldo de cada analista:\n");
    for (int i = 0; i < MAX_ANALISTAS; i++) {
        printf("Analista %s: $%.2f\n", analistas[i].nombre, analistas[i].sueldo);
    }
    
    // f. Nombre del analista que cobró más
    printf("\nf) Analista que cobró más:\n");
    int mayorSueldo = 0;
    for (int i = 1; i < MAX_ANALISTAS; i++) {
        if (analistas[i].sueldo > analistas[mayorSueldo].sueldo) {
            mayorSueldo = i;
        }
    }
    printf("Analista %s cobró más: $%.2f\n", 
           analistas[mayorSueldo].nombre, analistas[mayorSueldo].sueldo);
    
    // g. Cantidad de analistas que hayan trabajado menos de 5 hs en alguno de los proyectos
    printf("\ng) Analistas que trabajaron menos de %d hs en algún proyecto:\n", HORAS_MINIMAS);
    int contador = 0;
    for (int i = 0; i < MAX_ANALISTAS; i++) {
        int encontrado = 0;  // Flag para evitar usar break
        for (int j = 0; j < MAX_PROYECTOS && !encontrado; j++) {
            if (horasAnalistaProyecto[i][j] > 0 && horasAnalistaProyecto[i][j] < HORAS_MINIMAS) {
                printf("Analista %s trabajó %.2f horas en proyecto %d\n", 
                       analistas[i].nombre, horasAnalistaProyecto[i][j], j + 1);
                contador++;
                encontrado = 1;  // Marcar como encontrado para salir del bucle
            }
        }
    }
    printf("Total de analistas: %d\n", contador);
    
    // h. Imprimir ordenado por sueldo descendente
    printf("\nh) Analistas ordenados por sueldo (descendente):\n");
    struct Analista temp;
    // Ordenamiento burbuja por sueldo
    for (int i = 0; i < MAX_ANALISTAS - 1; i++) {
        for (int j = 0; j < MAX_ANALISTAS - 1 - i; j++) {
            if (analistas[j].sueldo < analistas[j + 1].sueldo) {
                temp = analistas[j];
                analistas[j] = analistas[j + 1];
                analistas[j + 1] = temp;
            }
        }
    }
    
    for (int i = 0; i < MAX_ANALISTAS; i++) {
        printf("Analista: %s, Valor hora: $%.2f, Sueldo: $%.2f\n", 
               analistas[i].nombre, analistas[i].valorHora, analistas[i].sueldo);
    }
    
    return 0;
}
