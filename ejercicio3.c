#include <stdio.h>
#include <string.h>
#include <float.h>

// Constantes
#define MAX_ANALISTAS 10
#define MAX_PROYECTOS 15
#define MAX_PLANILLAS 100
#define MAX_NOMBRE 50

// Funciones del programa
void cargarAnalistas(char nombres[][MAX_NOMBRE], float valorHora[]);
void cargarPlanillas(int numeroAnalista[], int numeroProyecto[], float horasTrabajadas[], int *numPlanillas);
void procesarDatos(char nombres[][MAX_NOMBRE], float valorHora[], int numeroAnalista[], int numeroProyecto[], 
                   float horasTrabajadas[], int numPlanillas, float totalHoras[], float horasProyecto[], 
                   float horasAnalistaProyecto[][MAX_PROYECTOS]);
void calcularSueldos(float valorHora[], float totalHoras[], float sueldos[]);
void mostrarHorasTotales(char nombres[][MAX_NOMBRE], float totalHoras[]);
void mostrarHorasAnalistaProyecto(char nombres[][MAX_NOMBRE], float horasAnalistaProyecto[][MAX_PROYECTOS]);
void mostrarHorasProyecto(float horasProyecto[]);
void buscarMenorProyecto1(char nombres[][MAX_NOMBRE], float horasAnalistaProyecto[][MAX_PROYECTOS]);
void mostrarSueldos(char nombres[][MAX_NOMBRE], float sueldos[]);
void buscarMayorSueldo(char nombres[][MAX_NOMBRE], float sueldos[]);
void contarAnalistas5Horas(char nombres[][MAX_NOMBRE], float horasAnalistaProyecto[][MAX_PROYECTOS]);
void ordenarPorSueldo(char nombres[][MAX_NOMBRE], float valorHora[], float sueldos[]);
void mostrarOrdenados(char nombres[][MAX_NOMBRE], float valorHora[], float sueldos[]);

int main() {
    // Arrays para almacenar los datos
    char nombres[MAX_ANALISTAS][MAX_NOMBRE];
    float valorHora[MAX_ANALISTAS];
    float totalHoras[MAX_ANALISTAS] = {0};
    float sueldos[MAX_ANALISTAS] = {0};
    
    // Arrays para las planillas
    int numeroAnalista[MAX_PLANILLAS];
    int numeroProyecto[MAX_PLANILLAS];
    float horasTrabajadas[MAX_PLANILLAS];
    int numPlanillas = 0;
    
    // Arrays para los calculos
    float horasProyecto[MAX_PROYECTOS] = {0};
    float horasAnalistaProyecto[MAX_ANALISTAS][MAX_PROYECTOS] = {0};
    
    printf("=== SISTEMA DE CONSULTORA ===\n");
    
    // Cargar datos de analistas
    cargarAnalistas(nombres, valorHora);
    
    // Cargar planillas
    cargarPlanillas(numeroAnalista, numeroProyecto, horasTrabajadas, &numPlanillas);
    
    // Procesar datos
    procesarDatos(nombres, valorHora, numeroAnalista, numeroProyecto, horasTrabajadas, 
                  numPlanillas, totalHoras, horasProyecto, horasAnalistaProyecto);
    
    // Calcular sueldos
    calcularSueldos(valorHora, totalHoras, sueldos);
    
    // Mostrar resultados
    printf("\n=== RESULTADOS ===\n");
    mostrarHorasTotales(nombres, totalHoras);
    mostrarHorasAnalistaProyecto(nombres, horasAnalistaProyecto);
    mostrarHorasProyecto(horasProyecto);
    buscarMenorProyecto1(nombres, horasAnalistaProyecto);
    mostrarSueldos(nombres, sueldos);
    buscarMayorSueldo(nombres, sueldos);
    contarAnalistas5Horas(nombres, horasAnalistaProyecto);
    ordenarPorSueldo(nombres, valorHora, sueldos);
    mostrarOrdenados(nombres, valorHora, sueldos);
    
    return 0;
}

// Funcion para cargar los datos de los analistas
void cargarAnalistas(char nombres[][MAX_NOMBRE], float valorHora[]) {
    printf("\n--- CARGAR ANALISTAS ---\n");
    for (int i = 0; i < MAX_ANALISTAS; i++) {
        printf("Ingrese nombre del analista %d: ", i + 1);
        scanf("%s", nombres[i]);
        printf("Ingrese valor hora del analista %d: ", i + 1);
        scanf("%f", &valorHora[i]);
    }
}

// Funcion para cargar las planillas
void cargarPlanillas(int numeroAnalista[], int numeroProyecto[], float horasTrabajadas[], int *numPlanillas) {
    printf("\n--- CARGAR PLANILLAS ---\n");
    printf("Ingrese las planillas (0 en numero de analista para terminar):\n");
    
    int continuar = 1;
    while (continuar) {
        printf("\nPlanilla %d:\n", (*numPlanillas) + 1);
        printf("Numero de analista (1-10, 0 para terminar): ");
        scanf("%d", &numeroAnalista[*numPlanillas]);
        
        if (numeroAnalista[*numPlanillas] == 0) {
            continuar = 0;
        }
        else if (numeroAnalista[*numPlanillas] < 1 || numeroAnalista[*numPlanillas] > MAX_ANALISTAS) {
            printf("Error: Numero de analista debe ser entre 1 y %d\n", MAX_ANALISTAS);
        }
        else {
            printf("Numero de proyecto (1-15): ");
            scanf("%d", &numeroProyecto[*numPlanillas]);
            
            if (numeroProyecto[*numPlanillas] < 1 || numeroProyecto[*numPlanillas] > MAX_PROYECTOS) {
                printf("Error: Numero de proyecto debe ser entre 1 y %d\n", MAX_PROYECTOS);
            }
            else {
                printf("Horas trabajadas: ");
                scanf("%f", &horasTrabajadas[*numPlanillas]);
                (*numPlanillas)++;
            }
        }
    }
}

// Funcion para procesar los datos de las planillas
void procesarDatos(char nombres[][MAX_NOMBRE], float valorHora[], int numeroAnalista[], int numeroProyecto[], 
                   float horasTrabajadas[], int numPlanillas, float totalHoras[], float horasProyecto[], 
                   float horasAnalistaProyecto[][MAX_PROYECTOS]) {
    
    for (int i = 0; i < numPlanillas; i++) {
        int analista = numeroAnalista[i] - 1;
        int proyecto = numeroProyecto[i] - 1;
        float horas = horasTrabajadas[i];
        
        // Acumular horas totales por analista
        totalHoras[analista] += horas;
        
        // Acumular horas por proyecto
        horasProyecto[proyecto] += horas;
        
        // Acumular horas por analista por proyecto
        horasAnalistaProyecto[analista][proyecto] += horas;
    }
}

// Funcion para calcular sueldos
void calcularSueldos(float valorHora[], float totalHoras[], float sueldos[]) {
    for (int i = 0; i < MAX_ANALISTAS; i++) {
        sueldos[i] = totalHoras[i] * valorHora[i];
    }
}

// Funcion para mostrar horas totales por analista
void mostrarHorasTotales(char nombres[][MAX_NOMBRE], float totalHoras[]) {
    printf("\n1) Horas totales por analista:\n");
    for (int i = 0; i < MAX_ANALISTAS; i++) {
        printf("   %s: %.2f horas\n", nombres[i], totalHoras[i]);
    }
}

// Funcion para mostrar horas por analista en cada proyecto
void mostrarHorasAnalistaProyecto(char nombres[][MAX_NOMBRE], float horasAnalistaProyecto[][MAX_PROYECTOS]) {
    printf("\n2) Horas por analista en cada proyecto:\n");
    for (int i = 0; i < MAX_ANALISTAS; i++) {
        printf("   %s:\n", nombres[i]);
        for (int j = 0; j < MAX_PROYECTOS; j++) {
            if (horasAnalistaProyecto[i][j] > 0) {
                printf("      Proyecto %d: %.2f horas\n", j + 1, horasAnalistaProyecto[i][j]);
            }
        }
    }
}

// Funcion para mostrar horas totales por proyecto
void mostrarHorasProyecto(float horasProyecto[]) {
    printf("\n3) Horas totales por proyecto:\n");
    for (int i = 0; i < MAX_PROYECTOS; i++) {
        if (horasProyecto[i] > 0) {
            printf("   Proyecto %d: %.2f horas\n", i + 1, horasProyecto[i]);
        }
    }
}

// Funcion para buscar analista que trabajo menos en proyecto 1
void buscarMenorProyecto1(char nombres[][MAX_NOMBRE], float horasAnalistaProyecto[][MAX_PROYECTOS]) {
    printf("\n4) Analista que trabajo menos en proyecto 1:\n");
    int menorAnalista = -1;
    float menorHoras = FLT_MAX;
    
    for (int i = 0; i < MAX_ANALISTAS; i++) {
        if (horasAnalistaProyecto[i][0] > 0 && horasAnalistaProyecto[i][0] < menorHoras) {
            menorHoras = horasAnalistaProyecto[i][0];
            menorAnalista = i;
        }
    }
    
    if (menorAnalista != -1) {
        printf("   %s trabajo menos en proyecto 1: %.2f horas\n", 
               nombres[menorAnalista], menorHoras);
    } else {
        printf("   Ningun analista trabajo en proyecto 1\n");
    }
}

// Funcion para mostrar sueldos
void mostrarSueldos(char nombres[][MAX_NOMBRE], float sueldos[]) {
    printf("\n5) Sueldo de cada analista:\n");
    for (int i = 0; i < MAX_ANALISTAS; i++) {
        printf("   %s: $%.2f\n", nombres[i], sueldos[i]);
    }
}

// Funcion para buscar analista con mayor sueldo
void buscarMayorSueldo(char nombres[][MAX_NOMBRE], float sueldos[]) {
    printf("\n6) Analista que cobro mas:\n");
    int mayorSueldo = 0;
    
    for (int i = 1; i < MAX_ANALISTAS; i++) {
        if (sueldos[i] > sueldos[mayorSueldo]) {
            mayorSueldo = i;
        }
    }
    
    printf("   %s cobro mas: $%.2f\n", 
           nombres[mayorSueldo], sueldos[mayorSueldo]);
}

// Funcion para contar analistas que trabajaron menos de 5 horas
void contarAnalistas5Horas(char nombres[][MAX_NOMBRE], float horasAnalistaProyecto[][MAX_PROYECTOS]) {
    printf("\n7) Analistas que trabajaron menos de 5 horas en algun proyecto:\n");
    int contador = 0;
    
    for (int i = 0; i < MAX_ANALISTAS; i++) {
        int encontrado = 0;
        for (int j = 0; j < MAX_PROYECTOS && !encontrado; j++) {
            if (horasAnalistaProyecto[i][j] > 0 && horasAnalistaProyecto[i][j] < 5) {
                printf("   %s trabajo %.2f horas en proyecto %d\n", 
                       nombres[i], horasAnalistaProyecto[i][j], j + 1);
                contador++;
                encontrado = 1;
            }
        }
    }
    printf("   Total: %d analistas\n", contador);
}

// Funcion para ordenar por sueldo usando burbuja
void ordenarPorSueldo(char nombres[][MAX_NOMBRE], float valorHora[], float sueldos[]) {
    char tempNombre[MAX_NOMBRE];
    float tempValor, tempSueldo;
    
    // Algoritmo de burbuja
    for (int i = 0; i < MAX_ANALISTAS - 1; i++) {
        for (int j = 0; j < MAX_ANALISTAS - 1 - i; j++) {
            if (sueldos[j] < sueldos[j + 1]) {
                // Intercambiar nombres
                strcpy(tempNombre, nombres[j]);
                strcpy(nombres[j], nombres[j + 1]);
                strcpy(nombres[j + 1], tempNombre);
                
                // Intercambiar valores hora
                tempValor = valorHora[j];
                valorHora[j] = valorHora[j + 1];
                valorHora[j + 1] = tempValor;
                
                // Intercambiar sueldos
                tempSueldo = sueldos[j];
                sueldos[j] = sueldos[j + 1];
                sueldos[j + 1] = tempSueldo;
            }
        }
    }
}

// Funcion para mostrar analistas ordenados
void mostrarOrdenados(char nombres[][MAX_NOMBRE], float valorHora[], float sueldos[]) {
    printf("\n8) Analistas ordenados por sueldo (descendente):\n");
    for (int i = 0; i < MAX_ANALISTAS; i++) {
        printf("   %s - Valor hora: $%.2f - Sueldo: $%.2f\n", 
               nombres[i], valorHora[i], sueldos[i]);
    }
}
