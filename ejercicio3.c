#include <stdio.h>

struct persona {
    char nombre[50];
    float precio;
    float horas;
    float plata;
};

struct trabajo {
    int persona;
    int proyecto;
    float tiempo;
};

int main() {
    struct persona gente[10];
    struct trabajo trabajos[50];
    float horasProyectos[15];
    float matriz[10][15];
    int cuantos = 0;
    int i, j;
    
    // poner en cero
    for (i = 0; i < 15; i++) {
        horasProyectos[i] = 0;
    }
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 15; j++) {
            matriz[i][j] = 0;
        }
    }
    
    printf("programa de trabajadores\n");
    printf("escriba los datos:\n");
    
    // leer gente
    for (i = 0; i < 10; i++) {
        printf("nombre persona %d: ", i + 1);
        scanf("%s", gente[i].nombre);
        printf("cuanto cobra por hora: ");
        scanf("%f", &gente[i].precio);
        gente[i].horas = 0;
        gente[i].plata = 0;
    }
    
    // leer trabajos
    printf("\nescribir trabajos hechos (0 para parar):\n");
    int seguir = 1;
    while (seguir) {
        printf("\ntrabajo numero %d:\n", cuantos + 1);
        printf("que persona (1 a 10, 0 para parar): ");
        scanf("%d", &trabajos[cuantos].persona);
        
        if (trabajos[cuantos].persona == 0) {
            seguir = 0;
        }
        else if (trabajos[cuantos].persona < 1 || trabajos[cuantos].persona > 10) {
            printf("mal numero\n");
        }
        else {
            printf("que proyecto (1 a 15): ");
            scanf("%d", &trabajos[cuantos].proyecto);
            
            if (trabajos[cuantos].proyecto < 1 || trabajos[cuantos].proyecto > 15) {
                printf("mal numero\n");
            }
            else {
                printf("cuantas horas: ");
                scanf("%f", &trabajos[cuantos].tiempo);
                cuantos++;
            }
        }
    }
    
    // hacer cuentas
    for (i = 0; i < cuantos; i++) {
        int cual = trabajos[i].persona - 1;
        int proyecto = trabajos[i].proyecto - 1;
        float tiempo = trabajos[i].tiempo;
        
        gente[cual].horas += tiempo;
        horasProyectos[proyecto] += tiempo;
        matriz[cual][proyecto] += tiempo;
    }
    
    // calcular plata
    for (i = 0; i < 10; i++) {
        gente[i].plata = gente[i].horas * gente[i].precio;
    }
    
    printf("\nRESULTADOS:\n");
    
    // a) cuantas horas trabajo cada uno
    printf("\na) horas de cada persona:\n");
    for (i = 0; i < 10; i++) {
        printf("%s: %.2f horas\n", gente[i].nombre, gente[i].horas);
    }
    
    // b) horas por persona en cada proyecto
    printf("\nb) horas de cada persona en cada proyecto:\n");
    for (i = 0; i < 10; i++) {
        printf("%s:\n", gente[i].nombre);
        for (j = 0; j < 15; j++) {
            if (matriz[i][j] > 0) {
                printf("  proyecto %d: %.2f horas\n", j + 1, matriz[i][j]);
            }
        }
    }
    
    // c) horas por proyecto
    printf("\nc) horas de cada proyecto:\n");
    for (i = 0; i < 15; i++) {
        if (horasProyectos[i] > 0) {
            printf("proyecto %d: %.2f horas\n", i + 1, horasProyectos[i]);
        }
    }
    
    // d) quien trabajo menos en proyecto 1
    printf("\nd) quien trabajo menos en proyecto 1:\n");
    int menor = -1;
    float minimo = 999999;
    for (i = 0; i < 10; i++) {
        if (matriz[i][0] > 0 && matriz[i][0] < minimo) {
            minimo = matriz[i][0];
            menor = i;
        }
    }
    if (menor != -1) {
        printf("%s trabajo menos: %.2f horas\n", gente[menor].nombre, minimo);
    } else {
        printf("nadie trabajo en proyecto 1\n");
    }
    
    // e) plata de cada uno
    printf("\ne) plata de cada persona:\n");
    for (i = 0; i < 10; i++) {
        printf("%s: $%.2f\n", gente[i].nombre, gente[i].plata);
    }
    
    // f) quien gano mas plata
    printf("\nf) quien gano mas:\n");
    int masPlata = 0;
    for (i = 1; i < 10; i++) {
        if (gente[i].plata > gente[masPlata].plata) {
            masPlata = i;
        }
    }
    printf("%s gano mas: $%.2f\n", gente[masPlata].nombre, gente[masPlata].plata);
    
    // g) los que trabajaron poco
    printf("\ng) los que trabajaron menos de 5 horas:\n");
    int contador = 0;
    for (i = 0; i < 10; i++) {
        int encontrado = 0;
        for (j = 0; j < 15 && encontrado == 0; j++) {
            if (matriz[i][j] > 0 && matriz[i][j] < 5) {
                printf("%s trabajo %.2f horas en proyecto %d\n", 
                       gente[i].nombre, matriz[i][j], j + 1);
                contador++;
                encontrado = 1;
            }
        }
    }
    printf("total: %d personas\n", contador);
    
    // h) ordenar por plata
    printf("\nh) ordenados por plata:\n");
    struct persona temp;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9 - i; j++) {
            if (gente[j].plata < gente[j + 1].plata) {
                temp = gente[j];
                gente[j] = gente[j + 1];
                gente[j + 1] = temp;
            }
        }
    }
    
    for (i = 0; i < 10; i++) {
        printf("%s - $%.2f por hora - total $%.2f\n", 
               gente[i].nombre, gente[i].precio, gente[i].plata);
    }
    
    return 0;
}