#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/patient.h"
#include "../include/filehandler.h"

#define NUM_NAMES 150
#define NAME_LENGTH 100

struct patient{
    int id;
    char *name;
    int timestamp;
    int time_exam;
};



// Private functions signatures
// Asinaturas das funções privadas




// OPERATIONS // OPERAÇÕES

Patient *patient_create(){
    /** \brief This function builds a patient object // Esta função constrói um objeto paciente
     *
     * \param id - Unique patient identification // Identificação única do paciente
     * \param name - Pointer to patient name // Ponteiro para o nome do paciente
     * \param birthdate - TM object with patient's birthday // Objeto TM com o aniversário do paciente
     * \return The patient object created // O objeto paciente criado
     *
     *          (EN) This function allocates memory for a new patient and initializes its fields with the given values.
     *          The TM structure passed as a parameter is copied to the new patient structure.
     *          If the name or birthdate pointers are NULL, the function prints an error message to stderr and returns NULL.
     *          If memory allocation fails, the function prints an error message to stderr and returns NULL.
     *\
     *\
     *          (PT)  Esta função aloca memória para um novo paciente e inicializa seus campos com os valores fornecidos.
     *          A estrutura TM passada como parâmetro é copiada para a nova estrutura do paciente.
     *          Se os ponteiros para name ou birthdate forem NULL, a função imprime uma mensagem de erro em stderr e retorna NULL.
     *          Se a alocação de memória falhar, a função imprime uma mensagem de erro em stderr e retorna NULL.
     *
     * \warning If the name or birthdate pointers are NULL, the function prints an error message to stderr and returns NULL.
     *          Se os ponteiros para name ou birthdate forem NULL, a função imprime uma mensagem de erro em stderr e retorna NULL.
     *
     * \warning If memory allocation fails, the function prints an error message to stderr and returns NULL
     *          Se a alocação de memória falhar, a função imprime uma mensagem de erro em stderr e retorna NULL.
     */

     // Allocates memory for patient structure
    // Aloca memória para estrutura paciente
    Patient *patient = (Patient *) calloc(1, sizeof(Patient));

    // Checks whether the allocation was successful
    // Verifica se a alocação foi bem-sucedida
    if(!patient){
        fprintf(stderr, "Failed to allocate memory for patient's structure");
        return NULL;
    }

    // Allocates memory for patient's name and checks whether the allocation was successful
    // Aloca memória para o nome do paciente e verifica se a alocação foi bem-sucedida
    patient->name = (char *) calloc(NAME_LENGTH + 1, sizeof(char));

    if(!patient->name) {
        fprintf(stderr, "Failed to allocate memory for name");
        patient_destroyer(patient);
        return NULL;
    }

    return patient;
}

void patient_destroyer(Patient *patient){
    /** \brief Free the allocated memory for the patient's structure // Libera memória para a estrutura do paciente
     *
     * \param patient - Pointer to patient's structure for free // Ponteiro para estrutura do paciente a ser liberada
     *
     * \details This function checks if the patient pointer is NULL. If not, it frees the memory allocated for the patient's name and birthdate, if they were allocated, and then frees the patient structure itself.
     * \details Esta função verifica se o ponteiro do paciente é NULL. Se não for, libera a memória alocada para o nome e data de nascimento do paciente, se estiverem alocados, e então libera a própria estrutura do paciente.
     *
     * \warning This function does not return any value. If the patient pointer is NULL, it simply returns without doing anything.
     *          Esta função não retorna nenhum valor. Se o ponteiro do paciente for NULL, simplesmente retorna sem fazer nada.
     */

    /* Checks if the patient pointer is NULL // Verifica se o ponteiro do paciente é nulo */
    if (!patient){
        return;
    }

    /* Free patient's name if allocated // Libera o nome do paciente, se alocado */
    if (patient->name) {
        free(patient->name);
        patient->name = NULL; // Set to NULL after freeing // Define como NULL após liberar
    }

    /* Free the patient structure itself // Libera a estrutura do paciente */
    free(patient);
}

const void patient_save(Patient *patient, const char *file_name, const char *str) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Builds the file handler
    // Constrói o manipulador de arquivos
    FileHandler *fh = fh_create(file_name);

    fh_write(fh, str);
    fh_destroyer(fh);
}

const char *patient_generation_random_name() {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Array of first names
    // Array de primeiros nomes
    const char *first_names[NUM_NAMES] = {
        "Lucas", "Maria", "João", "Ana", "Pedro", "Carla", "Rafael", "Fernanda", "Paulo", "Juliana",
        "Gabriel", "Isabela", "Matheus", "Beatriz", "Felipe", "Camila", "Daniel", "Letícia", "Rodrigo", "Mariana",
        "Bruno", "Larissa", "Thiago", "Aline", "Gustavo", "Amanda", "Vinícius", "Bruna", "Diego", "Natália",
        "Vitor", "Bianca", "André", "Vanessa", "Eduardo", "Gabriela", "Renato", "Carolina", "Alex", "Sabrina",
        "Henrique", "Patrícia", "Marcelo", "Rafaela", "Leonardo", "Tatiana", "Ricardo", "Jéssica", "Fernando", "Luana",
        "Miguel", "Renata", "César", "Viviane", "Rogério", "Verônica", "Jorge", "Eliane", "Leandro", "Cláudia",
        "Rafael", "Michele", "Ivan", "Tatiane", "Sérgio", "Cristiane", "Maurício", "Karina", "José", "Priscila",
        "Fábio", "Alessandra", "Luiz", "Suzana", "Rui", "Sônia", "Álvaro", "Rita", "Cauã", "Gisela",
        "Davi", "Lorena", "Alan", "Elis", "Adriano", "Sandra", "Murilo", "Joana", "Caio", "Renata",
        "Arthur", "Bárbara", "Roberto", "Tânia", "Iago", "Silvia", "Otávio", "Vera", "Nicolas", "Rosa",
        "Márcio", "Simone", "Evandro", "Helena", "Cássio", "Lúcia", "Hugo", "Regina", "Rodrigo", "Daniela",
        "Victor", "Evelyn", "Érico", "Clarice", "Flávio", "Fabiana", "Antônio", "Mônica", "Rômulo", "Cecília",
        "Patrick", "Rute", "Miguel", "Noemi", "Yuri", "Ângela", "Tales", "Estela", "Bruno", "Núbia",
        "Guilherme", "Lívia", "Samuel", "Elisa", "Otávio", "Denise", "Renan", "Melissa", "Edson", "Raquel",
        "Heitor", "Marta", "Augusto", "Neusa", "Saulo", "Débora", "Máximo", "Inês", "Gerson", "Clara"
    };

    // Array of last names
    // Array de sobrenomes
    const char *last_names[NUM_NAMES] = {
        "Silva", "Santos", "Oliveira", "Souza", "Pereira", "Lima", "Carvalho", "Ferreira", "Rodrigues", "Almeida",
        "Costa", "Martins", "Araújo", "Barbosa", "Ribeiro", "Correia", "Nascimento", "Campos", "Cardoso", "Gonçalves",
        "Moura", "Teixeira", "Monteiro", "Mendes", "Dias", "Rocha", "Andrade", "Moreira", "Vieira", "Nunes",
        "Moraes", "Freitas", "Sousa", "Tavares", "Cavalcante", "Borges", "Castro", "Reis", "Alves", "Lopes",
        "Figueiredo", "Fernandes", "Miranda", "Ramos", "Pinto", "Coelho", "Leal", "Simões", "Guimarães", "Fonseca",
        "Machado", "Brito", "Rosa", "Xavier", "Lima", "Duarte", "Gomes", "Farias", "Santiago", "Carone",
        "Pinheiro", "Amaral", "Lacerda", "Cunha", "Medeiros", "Cruz", "Maia", "Aguiar", "Pereira", "Barros",
        "Soares", "Peixoto", "Queiroz", "Sampaio", "Vasconcelos", "Sales", "Macedo", "Franco", "Lacerda", "Bittencourt",
        "Menezes", "Silveira", "Macedo", "Mendonça", "Queiroz", "Siqueira", "Abreu", "Amorim", "Camargo", "Torres",
        "Montenegro", "Bernardo", "Prado", "Neves", "Nóbrega", "Castro", "Braga", "Furtado", "de Paula", "Valente",
        "Paiva", "Cavalcanti", "Nogueira", "Bittencourt", "Serra", "Moraes", "Rezende", "Garcia", "Rangel", "Pinto",
        "César", "Cabrera", "Henriques", "Lopes", "Queirós", "Franco", "Farias", "Pimenta", "Ramos", "Cabral",
        "Geraldo", "Serrano", "Vargas", "Leite", "Farias", "Meireles", "Guedes", "Siqueira", "de Carvalho", "Amancio",
        "Nascimento", "Boulos", "Leal", "Lobo", "Pádua", "Marques", "Campos", "Azevedo", "Borgi", "Silveira"
    };

    // Generate a random index for the first name
    // Gera um índice aleatório para o primeiro nome
    int index_first_name = rand() % NUM_NAMES;

    // Generate a random index for the middle name
    // Gera um índice aleatório para o nome do meio
    int index_middle_name = rand() % NUM_NAMES;

    // Generate a random index for the last name
    // Gera um índice aleatório para o último
    int index_last_name = rand() % NUM_NAMES;

    // Ensure that the last name is different from the middle name
    // Garante que o último nome seja diferente do nome do meio
    do {
        index_last_name = rand() % NUM_NAMES;
    } while (index_last_name == index_middle_name);

    // Allocates memory to the full name
    // Alloca memória para o nome completo
    char *name = (char *) malloc(NAME_LENGTH * sizeof(char));

    // Checks whether the allocation was successful
    // Verifica se a alocação foi bem-sucedida
    if(!name) {
        fprintf(stderr, "Error: failed to allocate memory for name");
        return NULL;
    }

    // Format the full name
    // Formata o nome completo
    snprintf(name, NAME_LENGTH, "%s %s %s", first_names[index_first_name], last_names[index_middle_name], last_names[index_last_name]);

    return name;
}

int patient_generation_id(GenericQueue *q) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */

    int id;


    if (gq_is_empty(q)) {
        id = 1;
    } else {
        Patient *last_patient_queue = (Patient *) gq_peek_tail(q);
        id = last_patient_queue->id + 1;
    }

    return id;
}

const char *patient_format_to_string(const Patient *patient) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Static buffer to store the formatted patient
    // Buffer estático para armazenar o paciente formatado
    static char formatted_patient[256];

    // Format the patient object to string
    // Formata o objeto paciente para string
    snprintf(formatted_patient, sizeof(formatted_patient), "ID: %d\n Name: %s\n Time stamp: %d", patient->id, patient->name, patient->timestamp);

    return formatted_patient;
}


// GETTERS

const int patient_get_id(Patient *patient) {
    /** \brief This function gets and returns patient's ID // Esta função obtém e retorna o ID do paciente
     *
     * \param patient - Pointer to patient's structure // Ponteiro para a estrutura do paciente
     * \return The patient's ID // O ID do paciente
     *
     * \details This function checks if the patient pointer is NULL. If it is, it prints an error message to stderr and returns 1. Otherwise, it returns the patient's ID.
     * \details Esta função verifica se o ponteiro do paciente é NULL. Se for, imprime uma mensagem de erro em stderr e retorna 1. Caso contrário, retorna o ID do paciente.
     *
     * \warning If the patient pointer is NULL, the function prints an error message to stderr and returns 1.
     *          Se o ponteiro do paciente for NULL, a função imprime uma mensagem de erro em stderr e retorna 1.
     */

     /* Checks if the patient pointer is NULL // Verifica se o ponteiro do paciente é nulo */
     if (!patient){
        fprintf(stderr, "Error: NULL patient pointer");
        return 1;
     }

    return patient->id;
}

const char *patient_get_name(Patient *patient){
    /** \brief This function gets and returns patient's name // Esta função obtém e retorna o nome do paciente
     *
     * \param patient - Pointer to patient's structure // Ponteiro para a estrutura do paciente
     * \return The patient's name // O nome do paciente
     *
     * \details This function checks if the patient pointer is NULL. If it is, it prints an error message to stderr and returns NULL. Otherwise, it returns the patient's name.
     * \details Esta função verifica se o ponteiro do paciente é NULL. Se for, imprime uma mensagem de erro em stderr e retorna NULL. Caso contrário, retorna o nome do paciente.
     *
     * \warning If the patient pointer is NULL, the function prints an error message to stderr and returns NULL.
     *          Se o ponteiro do paciente for NULL, a função imprime uma mensagem de erro em stderr e retorna NULL.
     */

     /* Checks if the patient pointer is NULL // Verifica se o ponteiro do paciente é nulo */
     if (!patient){
        fprintf(stderr, "Error: NULL patient pointer");
        return NULL;
     }

    return patient->name;
}

const int patient_get_timestamp(Patient *patient){
    /** \brief This function gets and returns patient's timestamp // Esta função obtém e retorna o timestamp do paciente
     *
     * \param patient - Pointer to patient's structure // Ponteiro para a estrutura do paciente
     * \return Pointer to const struct tm representing the patient's timestamp // Ponteiro para const struct tm representando o timestamp do paciente
     *
     * \details This function checks if the patient pointer is NULL. If it is, it prints an error message to stderr and returns NULL. Otherwise, it returns the patient's timestamp.
     * \details Esta função verifica se o ponteiro do paciente é NULL. Se for, imprime uma mensagem de erro em stderr e retorna NULL. Caso contrário, retorna um ponteiro para o timestamp do paciente.
     *
     * \warning If the patient pointer is NULL, the function prints an error message to stderr and returns NULL.
     *          Se o ponteiro do paciente for NULL, a função imprime uma mensagem de erro em stderr e retorna NULL.
     */

     /* Checks if the patient pointer is NULL // Verifica se o ponteiro do paciente é nulo */
     if (!patient){
        fprintf(stderr, "Error: NULL patient pointer");
        return -1;
     }

    return patient->timestamp;
};

int patient_get_time_exam(Patient *patient) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if the patient pointer is NULL
    // Verifica se o ponteiro do paciente é nulo
     if (!patient){
        fprintf(stderr, "In function 'patient_get_exam_time' \nError: NULL patient pointer \n");
        return -1;
     }

     return patient->time_exam;
}

// SETTERS

void patient_set_id(Patient *patient, const int id) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    /* Checks if the patient pointer is NULL // Verifica se o ponteiro do paciente é nulo */
     if (!patient){
        fprintf(stderr, "Error: NULL patient pointer");
        return;
     }

    patient->id = id;
}

void patient_set_name(Patient *patient, const char *name) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    /* Checks if the patient pointer is NULL // Verifica se o ponteiro do paciente é nulo */
     if (!patient){
        fprintf(stderr, "Error: NULL patient pointer");
        return;
     }

    /* Copy the name // Copia o nome */
    strcpy(patient->name, name);
}

void patient_set_timestamp(Patient *patient, const int timestamp) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */

    /* Checks if the patient pointer is NULL // Verifica se o ponteiro do paciente é nulo */
     if (!patient){
        fprintf(stderr, "Error: NULL patient pointer");
        return;
     }

     patient->timestamp = timestamp;
}

void patient_set_exam_time(Patient *patient, int time_exam) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if the patient pointer is NULL
    // Verifica se o ponteiro do paciente é nulo
     if (!patient){
        fprintf(stderr, "In function 'patient_set_exam_time' \nError: NULL patient pointer \n");
        return;
     }

     patient->time_exam = time_exam;
}



// PRIVATE FUNCTIONS // FUNÇÕES PRIVADAS

