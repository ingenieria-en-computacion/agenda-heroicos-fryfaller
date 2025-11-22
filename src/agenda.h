#ifndef agenda_h
#define agenda_h

#define MAX_CONTACTOS 100
#define MAX_CADENA 50
#define ARCHIVO_DATOS "contactos.txt"

typedef enum {
    CASA = 1,
    MOVIL,
    OFICINA
} TipoTelefono;

typedef struct {
    char nombre[MAX_CADENA];
    char apellido[MAX_CADENA];
    int dia_nacimiento;
    int mes_nacimiento;
    char telefono[MAX_CADENA];
    TipoTelefono tipo_telefono;
} Contacto;

typedef struct {
    Contacto contactos[MAX_CONTACTOS];
    int total_contactos;
} Agenda;

/**
 * @brief Inicializa la agenda, poniendo el contador de contactos a cero.
 * @param agenda Puntero a la estructura Agenda a inicializar.
 */
void inicializar_agenda(Agenda *agenda);

/**
 * @brief Muestra el menú principal y obtiene la opción seleccionada por el usuario.
 * @return Opción del menú (entero).
 */
int mostrar_menu();

/**
 * @brief Agrega un nuevo contacto a la agenda.
 * @param agenda Puntero a la estructura Agenda.
 */
void agregar_contacto(Agenda *agenda);

/**
 * @brief Imprime todos los contactos registrados en la agenda.
 * @param agenda Puntero a la estructura Agenda.
 */
void imprimir_contactos(const Agenda *agenda);

/**
 * @brief Busca un contacto por nombre o número de teléfono.
 * @param agenda Puntero a la estructura Agenda.
 */
void buscar_contacto(const Agenda *agenda);

/**
 * @brief Ordena los contactos en la agenda alfabéticamente por nombre.
 * Utiliza el algoritmo de la burbuja (ascendente).
 * @param agenda Puntero a la estructura Agenda.
 */
void ordenar_contactos(Agenda *agenda);

/**
 * @brief Guarda todos los contactos de la agenda en un archivo de texto.
 * @param agenda Puntero a la estructura Agenda.
 * @return 1 si la operación fue exitosa, 0 en caso contrario.
 */
int guardar_contactos(const Agenda *agenda);

/**
 * @brief Carga contactos desde un archivo de texto a la agenda.
 * @param agenda Puntero a la estructura Agenda.
 * @return 1 si la operación fue exitosa, 0 en caso contrario.
 */
int cargar_contactos(Agenda *agenda);

// -----------------------------------------------------------

#endif // AGENDA_H
