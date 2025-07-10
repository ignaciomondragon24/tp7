#include <stdio.h>

// Función para ordenamiento burbuja
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Función para búsqueda secuencial
int busquedaSecuencial(int arr[], int n, int buscar) {
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] == buscar) {
            return i;
        }
    }
    return -1;
}

// Función para búsqueda binaria
int busquedaBinaria(int arr[], int n, int buscar) {
    int inicio = 0, fin = n - 1, medio;
    
    while (inicio <= fin) {
        medio = (inicio + fin) / 2;
        if (arr[medio] == buscar) {
            return medio;
        }
        if (arr[medio] < buscar) {
            inicio = medio + 1;
        } else {
            fin = medio - 1;
        }
    }
    return -1;
}

int main() {
    int vector[10];
    int i, opcion, buscar, resultado;
    
    printf("=== EJERCICIO 2: BUSQUEDA EN VECTOR ===\n");
    printf("Ingrese 10 números:\n");
    
    // Cargar números
    for (i = 0; i < 10; i++) {
        printf("Número %d: ", i + 1);
        scanf("%d", &vector[i]);
    }
    
    // Ordenar para búsqueda binaria
    bubbleSort(vector, 10);
    
    printf("\nVector ordenado: ");
    for (i = 0; i < 10; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
    
    printf("\nIngrese el número a buscar: ");
    scanf("%d", &buscar);
    
    printf("\nSeleccione el tipo de búsqueda:\n");
    printf("1. Búsqueda secuencial\n");
    printf("2. Búsqueda binaria\n");
    printf("Opción: ");
    scanf("%d", &opcion);
    
    switch (opcion) {
        case 1:
            resultado = busquedaSecuencial(vector, 10, buscar);
            if (resultado != -1) {
                printf("Número encontrado en la posición %d (búsqueda secuencial)\n", resultado + 1);
            } else {
                printf("Número no encontrado (búsqueda secuencial)\n");
            }
            break;
        case 2:
            resultado = busquedaBinaria(vector, 10, buscar);
            if (resultado != -1) {
                printf("Número encontrado en la posición %d (búsqueda binaria)\n", resultado + 1);
            } else {
                printf("Número no encontrado (búsqueda binaria)\n");
            }
            break;
        default:
            printf("Opción inválida\n");
    }
    
    return 0;
}
