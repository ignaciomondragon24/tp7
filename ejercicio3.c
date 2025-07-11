#include <stdio.h>
#include <string.h> // Agregado para usar strcpy

int main() {
    char nombre[10][50];
    float costoHora[10];
    float tiempoTotal[10] = {0};
    float pagoTotal[10] = {0};
    float tiemposPorProyecto[15] = {0};
    float matriz[10][15] = {0};
    int numEmpleado, numProyecto, totalRegistros = 0;
    float tiempoTrabajado;
    int i, j;

    printf("SISTEMA DE CONTROL DE EMPLEADOS Y PROYECTOS\n");
    printf("Ingresa la informacion de los empleados:\n\n");
    for (i = 0; i < 10; i++) {
        printf("Empleado numero %d:\n", i + 1);
        printf("  Nombre: ");
        scanf("%s", nombre[i]);
        printf("  Valor por hora: $");
        scanf("%f", &costoHora[i]);
    }

    printf("\nAhora ingresa los registros de trabajo (0 para salir):\n");
    printf("Registro %d:\n", totalRegistros + 1);
    printf("  Numero de empleado (1-10, 0 para salir): ");
    scanf("%d", &numEmpleado);
    while (numEmpleado != 0) {
        if (numEmpleado < 1 || numEmpleado > 10) {
            printf("  Error: debe ser entre 1 y 10\n\n");
        } else {
            printf("  Numero de proyecto (1-15): ");
            scanf("%d", &numProyecto);
            if (numProyecto < 1 || numProyecto > 15) {
                printf("  Error: debe ser entre 1 y 15\n\n");
            } else {
                printf("  Horas trabajadas: ");
                scanf("%f", &tiempoTrabajado);
                tiempoTotal[numEmpleado-1] += tiempoTrabajado;
                tiemposPorProyecto[numProyecto-1] += tiempoTrabajado;
                matriz[numEmpleado-1][numProyecto-1] += tiempoTrabajado;
                totalRegistros++;
                printf("\n");
            }
        }
        printf("Registro %d:\n", totalRegistros + 1);
        printf("  Numero de empleado (1-10, 0 para salir): ");
        scanf("%d", &numEmpleado);
    }

    for (i = 0; i < 10; i++) {
        pagoTotal[i] = tiempoTotal[i] * costoHora[i];
    }

    printf("\n======= RESULTADOS DEL ANALISIS =======\n");
    printf("\na) Tiempo total trabajado por cada empleado:\n");
    for (i = 0; i < 10; i++) {
        printf("   %s: %.2f horas\n", nombre[i], tiempoTotal[i]);
    }
    printf("\nb) Tiempo de cada empleado en cada proyecto:\n");
    for (i = 0; i < 10; i++) {
        printf("   %s:\n", nombre[i]);
        for (j = 0; j < 15; j++) {
            if (matriz[i][j] > 0) {
                printf("     Proyecto %d: %.2f horas\n", j + 1, matriz[i][j]);
            }
        }
    }
    printf("\nc) Tiempo total trabajado en cada proyecto:\n");
    for (i = 0; i < 15; i++) {
        if (tiemposPorProyecto[i] > 0) {
            printf("   Proyecto %d: %.2f horas\n", i + 1, tiemposPorProyecto[i]);
        }
    }
    printf("\nd) Empleado que menos trabajo en proyecto 1:\n");
    int empleadoMenor = -1;
    float tiempoMenor = 9999.0;
    for (i = 0; i < 10; i++) {
        if (matriz[i][0] > 0 && matriz[i][0] < tiempoMenor) {
            tiempoMenor = matriz[i][0];
            empleadoMenor = i;
        }
    }
    if (empleadoMenor >= 0) {
        printf("   %s trabajo %.2f horas en proyecto 1\n", nombre[empleadoMenor], tiempoMenor);
    } else {
        printf("   Ningun empleado trabajo en proyecto 1\n");
    }
    printf("\ne) Pago total de cada empleado:\n");
    for (i = 0; i < 10; i++) {
        printf("   %s: $%.2f\n", nombre[i], pagoTotal[i]);
    }
    printf("\nf) Empleado que mas dinero cobro:\n");
    int empleadoMayor = 0;
    for (i = 1; i < 10; i++) {
        if (pagoTotal[i] > pagoTotal[empleadoMayor]) {
            empleadoMayor = i;
        }
    }
    printf("   %s cobro $%.2f\n", nombre[empleadoMayor], pagoTotal[empleadoMayor]);
    printf("\ng) Empleados con menos de 5 horas en algun proyecto:\n");
    int contador = 0;
    for (i = 0; i < 10; i++) {
        int yaEncontrado = 0;
        for (j = 0; j < 15 && !yaEncontrado; j++) {
            if (matriz[i][j] > 0 && matriz[i][j] < 5.0) {
                printf("   %s trabajo %.2f horas en proyecto %d\n", nombre[i], matriz[i][j], j + 1);
                contador++;
                yaEncontrado = 1;
            }
        }
    }
    printf("   Total de empleados: %d\n", contador);
    // h) Empleados ordenados por pago total (mayor a menor):
    printf("\nh) Ranking de empleados por pago total (de mayor a menor):\n");
    // Ordenamiento burbuja mejorado
    for (i = 0; i < 10 - 1; i++) {
        for (j = 0; j < 10 - 1 - i; j++) {
            if (pagoTotal[j] < pagoTotal[j + 1]) {
                // Intercambiar todos los datos asociados
                float auxPago = pagoTotal[j];
                pagoTotal[j] = pagoTotal[j + 1];
                pagoTotal[j + 1] = auxPago;
                float auxHora = costoHora[j];
                costoHora[j] = costoHora[j + 1];
                costoHora[j + 1] = auxHora;
                float auxTiempo = tiempoTotal[j];
                tiempoTotal[j] = tiempoTotal[j + 1];
                tiempoTotal[j + 1] = auxTiempo;
                char auxNombre[50];
                strcpy(auxNombre, nombre[j]);
                strcpy(nombre[j], nombre[j + 1]);
                strcpy(nombre[j + 1], auxNombre);
            }
        }
    }
    for (i = 0; i < 10; i++) {
        printf("   %2d) %-15s | $%7.2f/h | Total: $%8.2f\n", i+1, nombre[i], costoHora[i], pagoTotal[i]);
    }
    printf("\n¡Análisis finalizado!\n");
    return 0;
}
