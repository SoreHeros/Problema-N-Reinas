#include <stdio.h>
#include <stdlib.h>


long long int contador_actiertos = 0;
long long int contador_fallos = 0;
int min_bool = 0;
int imprimir_bool = 0;


typedef struct par{
    int x;
    int y;
}*p_par;

int abs(int n){
    if(n < 0)
        return -n;

    return n;
}

void imprimir_tablero(p_par combinacion, int len){
    //imprimir esquina arriba izquierda 201 = ╔
    printf("%c%c%c%c", 201, 205, 205, 205);

    //imprimir barra de arriba 205 = ═, 203 = ╦
    for(int i = 1; i < len; i++)
        printf("%c%c%c%c", 203, 205, 205, 205);

    //imprimir esquina derecha 187 = ╗
    printf("%c", 187);

    //imprimir primeras casillas 186 = ║, 219 = █
    printf("\n");
    for(int i = 0; i < len; i++) {
        if (combinacion[0].y == i)
            if ((i) % 2)
                printf("%c%cQ%c", 186, 219, 219);
            else
                printf("%c Q ", 186);
        else if (i % 2)
            printf("%c%c%c%c", 186, 219, 219, 219);
        else
            printf("%c   ", 186);
    }
    printf("%c", 186);

    //imprimir casillas genéricas 204 = ╠, 185 = ╣
    for(int i = 1; i < len; i++){
        //escribir barras separadoras 206 = ╬
        printf("\n%c%c%c%c", 204, 205, 205, 205);
        for(int j = 1; j < len; j++)
            printf("%c%c%c%c", 206, 205, 205, 205);
        printf("%c", 185);
        printf("\n");
        //escribir casillas
        for(int j = 0; j < len; j++){
            if (combinacion[i].y == j) {
                if ((i+j) % 2)
                    printf("%c%cQ%c", 186, 219, 219);
                else
                    printf("%c Q ", 186);
            }else if ((i+j) % 2)
                printf("%c%c%c%c", 186, 219, 219, 219);
            else
                printf("%c   ", 186);
        }
        printf("%c   ", 186);
    }

    //imprimir esquina abajo derecha 200 = ╚
    printf("\n%c%c%c%c", 200, 205, 205, 205);

    //imprimir barra de abajo 202 = ╩
    for(int i = 1; i < len; i++)
        printf("%c%c%c%c", 202, 205, 205, 205);

    //imprimir esquina derecha 188 = ╝
    printf("%c", 188);

}


void imprimir_array(p_par combinacion, int len){
    printf("\n");
    for(int i = 0; i < len; i++){
        printf("[%i,%i] ", combinacion[i].x, combinacion[i].y);
    }
    printf("\n");
}

int comprobar_colision(struct par candidato, p_par array){
    for(int i = 0; i < candidato.x; i++){
        if(candidato.y == array[i].y || abs(candidato.x - array[i].x) == abs(candidato.y - array[i].y))
            return 0;
    }

    return 1;
}


void combinacion_recursiva(p_par combinacion, int len, int prof){
    if(prof >= len){
        contador_actiertos++;
        if(imprimir_bool) {
            printf("\n");
            imprimir_array(combinacion, len);
            imprimir_tablero(combinacion, len);
        }
        if(min_bool == 1)
            min_bool = 2;
    } else {
        combinacion[prof].x = prof;
        for(int i = 0; i < len && min_bool != 2; i++){
            combinacion[prof].y = i;
            if(comprobar_colision(combinacion[prof], combinacion))
                combinacion_recursiva(combinacion, len, prof + 1);
            else
                contador_fallos++;
        }
    }
}

void buscar_combinacion(p_par combinacion, int len){
    combinacion[0].x = 0;
    for(int i = 0; i < len && min_bool != 2; i++){
        combinacion[0].y = i;
        combinacion_recursiva(combinacion, len, 1);
    }
}


int main() {
    p_par combinacion;
    long long int *combinaciones;
    long long int *fallidas;
    int tamano_max;
    printf("\nIntroduzca el tamano maximo: ");
    scanf("%i", &tamano_max);
    printf("\nImprimir tableros: ");
    scanf("%i", &imprimir_bool);
    printf("\nParar en el primer tablero: ");
    scanf("%i", &min_bool);


    combinaciones = malloc(tamano_max * sizeof(long long int));
    fallidas = malloc(tamano_max * sizeof(long long int));

    for(int i = 1; i <= tamano_max; i++) {
        printf("\n\n\n\n\nTamano %i:", i);
        combinacion = (p_par) malloc(i * sizeof(struct par));
        buscar_combinacion(combinacion, i);
        free(combinacion);

        printf("\n\nCombinaciones validas para tamano %i: %lli\n", i, contador_actiertos);
        printf("Combinaciones fallidas para tamano %i: %lli\n", i, contador_fallos);
        printf("Combinaciones totales para tamano %i: %lli\n", i, contador_fallos+contador_actiertos);
        combinaciones[i-1] = contador_actiertos;
        fallidas[i-1] = contador_fallos;
        if(min_bool == 2)
            min_bool = 1;
        contador_actiertos = 0;
        contador_fallos = 0;
    }

    //imprimir el contador_actiertos al final
    printf("\n\n\n\n\n\n\n\n");
    for(int i = 1; i <= tamano_max; i++){
        printf("Combinaciones validas para tamano %i: %lli\n", i, combinaciones[i-1]);
        printf("Combinaciones fallidas para tamano %i: %lli\n", i, fallidas[i-1]);
        printf("Combinaciones totales para tamano %i: %lli\n\n\n", i, fallidas[i-1]+combinaciones[i-1]);
    }

    free(combinaciones);
    return 0;
}
