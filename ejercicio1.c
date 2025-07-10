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

int main() {
    int vector[20];
    int i;
    
    printf("=== EJERCICIO 1: ORDENAMIENTO POR BURBUJEO ===\n");
    printf("Ingrese 20 valores:\n");
    
    // Cargar valores
    for (i = 0; i < 20; i++) {
        printf("Valor %d: ", i + 1);
        scanf("%d", &vector[i]);
    }
    
    // Ordenar usando bubble sort
    bubbleSort(vector, 20);
    
    // Mostrar resultado
    printf("\nVector ordenado:\n");
    for (i = 0; i < 20; i++) {
        printf("%d ", vector[i]);
    }
    printf("\n");
    
    return 0;
}
