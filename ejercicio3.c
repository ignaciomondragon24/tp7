#include <stdio.h>
#include <string.h>

int main() {
    /* Arrays para almacenar datos de los 10 analistas */
    char nombres[10][30];
    float valor_hora[10];
    float horas_totales[10];
    float sueldos[10];
    
    /* Matriz para horas de cada analista en cada proyecto (10x15) */
    float matriz_horas[10][15];
    
    /* Array para horas totales por proyecto */
    float horas_proyecto[15];
    
    /* Variables para entrada de datos */
    int num_analista, num_proyecto;
    float horas;
    char continuar;
    
    /* Variables para busquedas */
    int analista_menos_proy1;
    float min_horas_proy1;
    int analista_max_sueldo;
    float max_sueldo;
    int contador_menos_5h;
    
    /* Variables para ordenamiento */
    int i, j;
    char temp_nombre[30];
    float temp_valor, temp_sueldo;
    
    printf("=== SISTEMA CONSULTORA - GESTION DE ANALISTAS ===\n\n");
    
    /* Inicializar arrays en cero */
    for (i = 0; i < 10; i++) {
        horas_totales[i] = 0;
        for (j = 0; j < 15; j++) {
            matriz_horas[i][j] = 0;
        }
    }
    
    for (i = 0; i < 15; i++) {
        horas_proyecto[i] = 0;
    }
    
    /* Cargar datos de los 10 analistas */
    printf("1. CARGA DE DATOS DE ANALISTAS\n");
    printf("--------------------------------\n");
    for (i = 0; i < 10; i++) {
        printf("Analista %d:\n", i + 1);
        printf("  Nombre: ");
        scanf("%s", nombres[i]);
        printf("  Valor por hora: $");
        scanf("%f", &valor_hora[i]);
        printf("\n");
    }
    
    /* Cargar planillas de trabajo */
    printf("2. CARGA DE PLANILLAS DE TRABAJO\n");
    printf("---------------------------------\n");
    printf("Ingrese los datos de trabajo:\n");
    
    continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        printf("\nNúmero de analista (1-10): ");
        scanf("%d", &num_analista);
        
        printf("Número de proyecto (1-15): ");
        scanf("%d", &num_proyecto);
        
        printf("Horas trabajadas: ");
        scanf("%f", &horas);
        
        /* Convertir a indices (restar 1) */
        num_analista = num_analista - 1;
        num_proyecto = num_proyecto - 1;
        
        /* Acumular horas en la matriz */
        matriz_horas[num_analista][num_proyecto] = matriz_horas[num_analista][num_proyecto] + horas;
        
        /* Acumular horas totales del analista */
        horas_totales[num_analista] = horas_totales[num_analista] + horas;
        
        /* Acumular horas totales del proyecto */
        horas_proyecto[num_proyecto] = horas_proyecto[num_proyecto] + horas;
        
        printf("¿Continuar? (s/n): ");
        scanf(" %c", &continuar);
    }
    
    /* Calcular sueldos */
    for (i = 0; i < 10; i++) {
        sueldos[i] = horas_totales[i] * valor_hora[i];
    }
    
    /* Buscar analista que menos trabajó en proyecto 1 BUSQUEDA SECUENCIAL */ 
    min_horas_proy1 = 999999;
    analista_menos_proy1 = 0;
    for (i = 0; i < 10; i++) {// Recorre todos los analistas (0-9)
        if (matriz_horas[i][0] > 0 && matriz_horas[i][0] < min_horas_proy1) {
            min_horas_proy1 = matriz_horas[i][0];
            analista_menos_proy1 = i;
        }
    }
    
    /* Buscar analista que más cobró */
    max_sueldo = sueldos[0];  // Supone que el primero es el máximo
    analista_max_sueldo = 0; // Guarda la posición del máximo
    for (i = 1; i < 10; i++) { // Empieza desde posición 1 (no 0)
        if (sueldos[i] > max_sueldo) { // Si encuentra uno mayor
            max_sueldo = sueldos[i];   // Actualiza el máximo valor
            analista_max_sueldo = i;   // Actualiza la posición
        }
    }
    
    /* Contar analistas con menos de 5 horas en algún proyecto */
    contador_menos_5h = 0;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 15; j++) {
            if (matriz_horas[i][j] > 0 && matriz_horas[i][j] < 5) {
                contador_menos_5h++;
                break; /* Solo contar una vez por analista */
            }
        }
    }
    
    /* MOSTRAR RESULTADOS */
    printf("\n\n=== RESULTADOS DEL ANÁLISIS ===\n");
    
    /* a) Horas trabajadas por cada analista */
    printf("\na) HORAS TRABAJADAS POR CADA ANALISTA:\n");
    printf("---------------------------------------\n");
    for (i = 0; i < 10; i++) {
        printf("   %s: %.1f horas\n", nombres[i], horas_totales[i]);
    }
    
    /* b) Horas de cada analista en cada proyecto */
    printf("\nb) HORAS POR ANALISTA EN CADA PROYECTO:\n");
    printf("----------------------------------------\n");
    for (i = 0; i < 10; i++) {
        printf("   %s:\n", nombres[i]);
        for (j = 0; j < 15; j++) {
            if (matriz_horas[i][j] > 0) {
                printf("     Proyecto %d: %.1f horas\n", j + 1, matriz_horas[i][j]);
            }
        }
        printf("\n");
    }
    
    /* c) Horas trabajadas por proyecto */
    printf("c) HORAS TRABAJADAS POR PROYECTO:\n");
    printf("----------------------------------\n");
    for (i = 0; i < 15; i++) {
        if (horas_proyecto[i] > 0) {
            printf("   Proyecto %d: %.1f horas\n", i + 1, horas_proyecto[i]);
        }
    }
    
    /* d) Analista que menos trabajó en proyecto 1 */
    printf("\nd) ANALISTA QUE MENOS TRABAJÓ EN PROYECTO 1:\n");
    printf("---------------------------------------------\n");
    if (min_horas_proy1 < 999999) {
        printf("   %s trabajó %.1f horas\n", nombres[analista_menos_proy1], min_horas_proy1);
    } else {
        printf("   Ningún analista trabajó en proyecto 1\n");
    }
    
    /* e) Sueldo de cada analista */
    printf("\ne) SUELDO DE CADA ANALISTA:\n");
    printf("----------------------------\n");
    for (i = 0; i < 10; i++) {
        printf("   %s: $%.2f\n", nombres[i], sueldos[i]);
    }
    
    /* f) Analista que más cobró */
    printf("\nf) ANALISTA QUE MÁS COBRÓ:\n");
    printf("--------------------------\n");
    printf("   %s cobró $%.2f\n", nombres[analista_max_sueldo], max_sueldo);
    
    /* g) Cantidad de analistas con menos de 5hs */
    printf("\ng) ANALISTAS CON MENOS DE 5 HORAS EN ALGÚN PROYECTO:\n");
    printf("----------------------------------------------------\n");
    printf("   Total: %d analistas\n", contador_menos_5h); 
    /* h) ORDENAMIENTO POR SUELDO (BURBUJA) */
    printf("\nh) ANALISTAS ORDENADOS POR SUELDO (MAYOR A MENOR):\n");
    printf("---------------------------------------------------\n");
    
    /* Ordenamiento burbuja - intercambiar posiciones */
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9 - i; j++) {
            /* Si el sueldo actual es menor que el siguiente, intercambiar */
            if (sueldos[j] < sueldos[j + 1]) {
                /* Intercambiar sueldos */
                temp_sueldo = sueldos[j];
                sueldos[j] = sueldos[j + 1];
                sueldos[j + 1] = temp_sueldo;
                
                /* Intercambiar nombres */
                strcpy(temp_nombre, nombres[j]);
                strcpy(nombres[j], nombres[j + 1]);
                strcpy(nombres[j + 1], temp_nombre);
                
                /* Intercambiar valores por hora */
                temp_valor = valor_hora[j];
                valor_hora[j] = valor_hora[j + 1];
                valor_hora[j + 1] = temp_valor;
            }
        }
    }
    /* Mostrar lista ordenada */
    for (i = 0; i < 10; i++) {
        printf("   %d. %s - $%.2f/hora - Sueldo: $%.2f\n", 
               i + 1, nombres[i], valor_hora[i], sueldos[i]);
    }
    
    printf("\n=== FIN DEL ANÁLISIS ===\n");
    
    return 0;
}
