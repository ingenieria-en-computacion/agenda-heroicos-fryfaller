#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"


/**
 * @brief Inicializa la agenda, poniendo el contador de contactos a cero.
 * @param agenda Puntero a la estructura Agenda a inicializar.
 * @pseudocodigo
 * INICIO
 * agenda->total_contactos <- 0
 * FIN
 */
void inicializar_agenda(Agenda *agenda) {
    agenda->total_contactos = 0;
}

/**
 * @brief Muestra el menú principal y obtiene la opción seleccionada por el usuario.
 * @return Opción del menú (entero).
 * @pseudocodigo
 * INICIO
 * MOSTRAR "Menú de Agenda de Contactos"
 * MOSTRAR opciones
 * LEER opcion
 * RETORNAR opcion
 * FIN
 */
int mostrar_menu() {
    int opcion;
    printf("\n--- Menu de Agenda de Contactos ---\n");
    printf("1. Agregar contacto\n");
    printf("2. Imprimir todos los contactos\n");
    printf("3. Buscar contacto\n");
    printf("4. Ordenar contactos (por nombre)\n");
    printf("5. Guardar contactos en archivo\n");
    printf("6. Cargar contactos desde archivo\n");
    printf("0. Salir\n");
    printf("Seleccione una opcion: ");
    scanf("%d", &opcion);
    while (getchar() != '\n'); 
    return opcion;
}

/**
 * @brief Agrega un nuevo contacto a la agenda.
 * @param agenda Puntero a la estructura Agenda.
 * @pseudocodigo
 * INICIO
 * SI agenda->total_contactos >= MAX_CONTACTOS ENTONCES
 * MOSTRAR "Agenda llena"
 * RETORNAR
 * FIN SI
 * indice <- agenda->total_contactos
 * MOSTRAR "Ingrese Nombre: "
 * LEER agenda->contactos[indice].nombre
 * MOSTRAR "Ingrese Apellido: "
 * LEER agenda->contactos[indice].apellido
 * ... (Leer el resto de los campos)
 * agenda->total_contactos <- agenda->total_contactos + 1
 * FIN
 */
void agregar_contacto(Agenda *agenda) {
    if (agenda->total_contactos >= MAX_CONTACTOS) {
        printf(" Error: La agenda está llena. No se pueden agregar más contactos.\n");
        return;
    }

    Contacto *nuevo = &agenda->contactos[agenda->total_contactos];

    printf("\n--- Nuevo Contacto ---\n");
    
    printf("Nombre: ");
    fgets(nuevo->nombre, MAX_CADENA, stdin);
    nuevo->nombre[strcspn(nuevo->nombre, "\n")] = 0; 
    
    printf("Apellido: ");
    fgets(nuevo->apellido, MAX_CADENA, stdin);
    nuevo->apellido[strcspn(nuevo->apellido, "\n")] = 0;
    
    printf("Dia de nacimiento (1-31): ");
    scanf("%d", &nuevo->dia_nacimiento);
    
    printf("Mes de nacimiento (1-12): ");
    scanf("%d", &nuevo->mes_nacimiento);
    while (getchar() != '\n'); 
    
    printf("Telefono: ");
    fgets(nuevo->telefono, MAX_CADENA, stdin);
    nuevo->telefono[strcspn(nuevo->telefono, "\n")] = 0;
    
    int tipo;
    printf("Tipo de telefono (1: CASA, 2: MOVIL, 3: OFICINA): ");
    scanf("%d", &tipo);
    nuevo->tipo_telefono = (TipoTelefono)tipo;
    while (getchar() != '\n'); 

    agenda->total_contactos++;
    printf("Contacto agregado con exito.\n");
}

/**
 * @brief Imprime todos los contactos registrados en la agenda.
 * @param agenda Puntero a la estructura Agenda (constante).
 * @pseudocodigo
 * INICIO
 * SI agenda->total_contactos == 0 ENTONCES
 * MOSTRAR "Agenda vacía"
 * RETORNAR
 * FIN SI
 * PARA i DESDE 0 HASTA agenda->total_contactos - 1 HACER
 * contacto <- agenda->contactos[i]
 * MOSTRAR datos de contacto
 * FIN PARA
 * FIN
 */
void imprimir_contactos(const Agenda *agenda) {
    if (agenda->total_contactos == 0) {
        printf("La agenda esta vacia.\n");
        return;
    }

    printf("\n--- Lista de Contactos (%d) ---\n", agenda->total_contactos);
    for (int i = 0; i < agenda->total_contactos; i++) {
        const Contacto *c = &agenda->contactos[i];
        
        const char *tipo_str;
        switch (c->tipo_telefono) {
            case CASA: tipo_str = "CASA"; break;
            case MOVIL: tipo_str = "MOVIL"; break;
            case OFICINA: tipo_str = "OFICINA"; break;
            default: tipo_str = "DESCONOCIDO"; break;
        }

        printf("%d. Nombre: %s %s\n", i + 1, c->nombre, c->apellido);
        printf("   Nacimiento: %02d/%02d\n", c->dia_nacimiento, c->mes_nacimiento);
        printf("   Telefono: %s (%s)\n", c->telefono, tipo_str);
        printf("-------------------------\n");
    }
}

/**
 * @brief Busca un contacto por nombre o número de teléfono.
 * @param agenda Puntero a la estructura Agenda (constante).
 * @pseudocodigo
 * INICIO
 * MOSTRAR "Buscar por (1: Nombre, 2: Teléfono): "
 * LEER opcion_busqueda
 * MOSTRAR "Ingrese valor a buscar: "
 * LEER valor
 * encontrado <- FALSO
 * PARA i DESDE 0 HASTA agenda->total_contactos - 1 HACER
 * contacto <- agenda->contactos[i]
 * SI (opcion_busqueda == 1 Y STR_IGUAL(contacto.nombre, valor)) O
 * (opcion_busqueda == 2 Y STR_IGUAL(contacto.telefono, valor)) ENTONCES
 * MOSTRAR datos de contacto
 * encontrado <- VERDADERO
 * FIN SI
 * FIN PARA
 * SI encontrado == FALSO ENTONCES
 * MOSTRAR "Contacto no encontrado"
 * FIN SI
 * FIN
 */
void buscar_contacto(const Agenda *agenda) {
    if (agenda->total_contactos == 0) {
        printf("La agenda está vacia. No hay contactos para buscar.\n");
        return;
    }
    
    int opcion_busqueda;
    char valor_busqueda[MAX_CADENA];
    int encontrados = 0;

    printf("\n--- Buscar Contacto ---\n");
    printf("Buscar por (1: Nombre, 2: Telefono): ");
    if (scanf("%d", &opcion_busqueda) != 1 || (opcion_busqueda != 1 && opcion_busqueda != 2)) {
        printf("Opcion de busqueda invalida.\n");
        while (getchar() != '\n'); 
        return;
    }
    while (getchar() != '\n'); 

    printf("Ingrese el valor a buscar: ");
    fgets(valor_busqueda, MAX_CADENA, stdin);
    valor_busqueda[strcspn(valor_busqueda, "\n")] = 0;

    printf("\n--- Resultados de la Busqueda ---\n");
    for (int i = 0; i < agenda->total_contactos; i++) {
        const Contacto *c = &agenda->contactos[i];
        
        int es_nombre = (opcion_busqueda == 1) && (strcmp(c->nombre, valor_busqueda) == 0);
        int es_telefono = (opcion_busqueda == 2) && (strcmp(c->telefono, valor_busqueda) == 0);

        if (es_nombre || es_telefono) {
            const char *tipo_str;
            switch (c->tipo_telefono) {
                case CASA: tipo_str = "CASA"; break;
                case MOVIL: tipo_str = "MOVIL"; break;
                case OFICINA: tipo_str = "OFICINA"; break;
                default: tipo_str = "DESCONOCIDO"; break;
            }
            
            printf("Encontrado: %s %s\n", c->nombre, c->apellido);
            printf("   Telefono: %s (%s)\n", c->telefono, tipo_str);
            printf("-------------------------\n");
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("No se encontraron contactos con ese valor.\n");
    }
}

/**
 * @brief Ordena los contactos en la agenda alfabéticamente por nombre (ascendente).
 * Utiliza el algoritmo de la burbuja.
 * @param agenda Puntero a la estructura Agenda.
 * @pseudocodigo (Algoritmo de la Burbuja Ascendente)
 * INICIO
 * N <- agenda->total_contactos
 * PARA i DESDE 0 HASTA N-2 HACER
 * PARA j DESDE 0 HASTA N-2-i HACER
 * SI nombre(agenda->contactos[j]) > nombre(agenda->contactos[j+1]) ENTONCES
 * INTERCAMBIAR agenda->contactos[j] CON agenda->contactos[j+1]
 * FIN SI
 * FIN PARA
 * FIN PARA
 * FIN
 */
void ordenar_contactos(Agenda *agenda) {
    if (agenda->total_contactos <= 1) {
        printf("No hay suficientes contactos para ordenar.\n");
        return;
    }
    
    int n = agenda->total_contactos;
    Contacto temp;
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(agenda->contactos[j].nombre, agenda->contactos[j+1].nombre) > 0) {
                temp = agenda->contactos[j];
                agenda->contactos[j] = agenda->contactos[j+1];
                agenda->contactos[j+1] = temp;
            }
        }
    }
    
    printf("Contactos ordenados alfabeticamente por nombre.\n");
}

/**
 * @brief Guarda todos los contactos de la agenda en un archivo de texto.
 * @param agenda Puntero a la estructura Agenda (constante).
 * @return 1 si la operación fue exitosa, 0 en caso contrario.
 * @pseudocodigo
 * INICIO
 * ABRIR archivo ARCHIVO_DATOS en modo escritura ("w")
 * SI archivo ES NULO ENTONCES
 * MOSTRAR "Error al abrir archivo"
 * RETORNAR 0
 * FIN SI
 * PARA i DESDE 0 HASTA agenda->total_contactos - 1 HACER
 * Escribir en archivo: nombre|apellido|dia|mes|telefono|tipo_telefono\n
 * FIN PARA
 * CERRAR archivo
 * RETORNAR 1
 * FIN
 */
int guardar_contactos(const Agenda *agenda) {
    FILE *archivo = fopen(ARCHIVO_DATOS, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo '%s' para escritura.\n", ARCHIVO_DATOS);
        return 0;
    }

    for (int i = 0; i < agenda->total_contactos; i++) {
        const Contacto *c = &agenda->contactos[i];
        fprintf(archivo, "%s|%s|%d|%d|%s|%d\n", 
                c->nombre, 
                c->apellido, 
                c->dia_nacimiento, 
                c->mes_nacimiento, 
                c->telefono, 
                c->tipo_telefono);
    }

    fclose(archivo);
    printf("Contactos guardados exitosamente en '%s'.\n", ARCHIVO_DATOS);
    return 1;
}

/**
 * @brief Carga contactos desde un archivo de texto a la agenda.
 * @param agenda Puntero a la estructura Agenda.
 * @return 1 si la operación fue exitosa, 0 en caso contrario.
 * @pseudocodigo
 * INICIO
 * ABRIR archivo ARCHIVO_DATOS en modo lectura ("r")
 * SI archivo ES NULO ENTONCES
 * MOSTRAR "Error al abrir archivo"
 * RETORNAR 0
 * FIN SI
 * mientras (LEER linea de archivo) HACER
 * SI agenda->total_contactos < MAX_CONTACTOS ENTONCES
 * contacto <- agenda->contactos[agenda->total_contactos]
 * // Parsear linea usando sscanf con el formato: nombre|apellido|dia|mes|telefono|tipo
 * SI lectura exitosa ENTONCES
 * agenda->total_contactos <- agenda->total_contactos + 1
 * FIN SI
 * FIN SI
 * FIN MIENTRAS
 * CERRAR archivo
 * RETORNAR 1
 * FIN
 */
int cargar_contactos(Agenda *agenda) {
    FILE *archivo = fopen(ARCHIVO_DATOS, "r");
    if (archivo == NULL) {
        printf("No se encontro el archivo de datos '%s'. Iniciando agenda vacia.\n", ARCHIVO_DATOS);
        return 0;
    }

    agenda->total_contactos = 0; 
    
    while (agenda->total_contactos < MAX_CONTACTOS && 
           fscanf(archivo, "%[^|]|%[^|]|%d|%d|%[^|]|%d\n", 
                  agenda->contactos[agenda->total_contactos].nombre,
                  agenda->contactos[agenda->total_contactos].apellido,
                  &agenda->contactos[agenda->total_contactos].dia_nacimiento,
                  &agenda->contactos[agenda->total_contactos].mes_nacimiento,
                  agenda->contactos[agenda->total_contactos].telefono,
                  (int *)&agenda->contactos[agenda->total_contactos].tipo_telefono) == 6) {
        
        agenda->total_contactos++;
    }

    fclose(archivo);
    printf("%d contactos cargados exitosamente desde '%s'.\n", agenda->total_contactos, ARCHIVO_DATOS);
    return 1;
}

int main() {
    Agenda mi_agenda;
    inicializar_agenda(&mi_agenda);

    cargar_contactos(&mi_agenda);

    int opcion;
    do {
        opcion = mostrar_menu();
        
        switch (opcion) {
            case 1:
                agregar_contacto(&mi_agenda);
                break;
            case 2:
                imprimir_contactos(&mi_agenda);
                break;
            case 3:
                buscar_contacto(&mi_agenda);
                break;
            case 4:
                ordenar_contactos(&mi_agenda);
                break;
            case 5:
                guardar_contactos(&mi_agenda);
                break;
            case 6:
                cargar_contactos(&mi_agenda);
                break;
            case 0:
                printf("\n Saliendo de la agenda\n");
                guardar_contactos(&mi_agenda); 
                break;
            default:
                printf("\n Opción no valida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 0);

    return 0;
}
