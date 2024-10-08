#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/exam.h"
#include "../include/filehandler.h"

struct exam{
    int id;
    int patient_id;
    int rx_id;
    int condition_ia;
    int time;
};



// OPERATIONS // OPERAÇÕES

Exam *exam_create(){
    /** \brief This function creates an exam object // Esta função cria um objeto de exame
     *
     * \param id - Unique identification of the exam // Identificação única do exame
     * \param patient_id - Unique patient identification // Identificação única do paciente
     * \param rx_id - Unique identification of the x-ray machine // Identificação única do aparelho de raio x
     * \param time - Exam time // Horário de realização do exame (struct tm*)
     * \return The exam object created // O objeto de exame criado
     *
     * \details This function allocates memory for an Exam structure, initializes its fields with the provided parameters,
     *          and returns a pointer to the created Exam object. It also handles errors related to memory allocation for
     *          the exam structure and exam time. If any allocation fails, it cleans up allocated memory and returns NULL.
     *
     * \details Esta função aloca memória para uma estrutura Exam, inicializa seus campos com os parâmetros fornecidos e
     *          retorna um ponteiro para o objeto Exam criado. Ela também trata erros relacionados à alocação de memória
     *          para a estrutura do exame e para o horário do exame. Se alguma alocação falhar, limpa a memória alocada e
     *          retorna NULL.
     *
     * \warning If the time parameter is NULL, an error message is printed to stderr and NULL is returned without
     *          allocating any memory.
     *          Se o parâmetro time for NULL, uma mensagem de erro é impressa no stderr e NULL é retornado sem
     *          alocar qualquer memória.
     */


    // Allocates memory for exam structure and checks whether the allocation was successful
    // Aloca memória para estrutura exame e verifica se a alocação foi bem-sucedida
    Exam *exam = (Exam *) calloc(1, sizeof(Exam));

    if(!exam){
        fprintf(stderr, "Failed to allocate memory for exam's structure");
        return NULL;
    }

    return exam;
}

void exam_destroyer(Exam *exam){
    /** \brief Free the allocated memory for the exam's structure // Libera memória para a estrutura do exame
     *
     * \param exam - Pointer to exam's structure to be freed // Ponteiro para estrutura do exame a ser liberada
     *
     * \details This function frees the memory allocated for the exam's structure and its associated resources,
     *          including the exam time if it was allocated.
     * \details Esta função libera a memória alocada para a estrutura do exame e seus recursos associados,
     *          incluindo o tempo do exame se estiver alocado.
     */

     // Checks if the exam pointer is NULL
     // Verifica se o ponteiro do exame é nulo
     if(!exam){
        return;
     }

     free(exam);
}

const char *exam_format_to_string(Exam *exam) {
    /** \brief Formats the Exam object as a string for display or storage.
     *
     * \param exam - Pointer to the Exam object.
     * \return A formatted string representation of the Exam object.
     *
     * \details This function creates a formatted string that includes the ID, patient ID, x-ray ID, condition description, and
     *          timestamp of the exam. It uses a static buffer to store the formatted string and returns a pointer to this buffer.
     *          If the Exam pointer is NULL, the function may result in undefined behavior.
     * \details Esta função cria uma string formatada que inclui o ID, ID do paciente, ID do raio-x, descrição da condição e
     *          carimbo de data/hora do exame. Ela utiliza um buffer estático para armazenar a string formatada e retorna um ponteiro
     *          para este buffer. Se o ponteiro Exam for NULL, a função pode resultar em comportamento indefinido.
     *
     * \warning Ensure that the Exam pointer is not NULL to avoid undefined behavior.
     * \warning Certifique-se de que o ponteiro Exam não seja NULL para evitar comportamento indefinido.
     */


    // Static buffer to store the formatted patient
    // Buffer estático para armazenar o paciente formatado
    static char formatted_exam[256];

    // Format the patient object to string
    // Formata o objeto paciente para string
    snprintf(formatted_exam, sizeof(formatted_exam), "ID: %d\n Patient ID: %d\n X-ray ID:%d\n IA condition:%s\n Time stamp: %d", exam->id, exam->patient_id,exam->rx_id ,exam_get_condition_code(exam),exam->time);

    return formatted_exam;
}

int exam_generate_random_id() {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    srand(time(NULL));

    return (rand() % 5000);
}


// GETTERS

const int exam_get_id(Exam *exam){
    /** \brief This function gets and returns the unique identification of the exam // Esta função
     *         obtém e retorna a identificação única do exame
     *
     * \param exam - Pointer to exam's structure // Ponteiro para a estrutura do exame
     * \return The exam's ID // O ID do exame
     *
     * \details This function retrieves the unique identification number of the exam.
     *          It checks if the exam pointer is NULL. If it is NULL, an error message is printed to stderr and
     *          the function returns 1.
     * \details Esta função recupera o número de identificação único do exame.
     *          Ela verifica se o ponteiro exam é NULL. Se for NULL, uma mensagem de erro é impressa em stderr e
     *          a função retorna 1.
     *
     * \warning If the exam pointer is NULL, this function prints an error message to stderr and returns 1.
     *          Se o ponteiro exam for NULL, esta função imprime uma mensagem de erro em stderr e retorna 1.
     */

     // Checks if the patient pointer is NULL
     // Verifica se o ponteiro do exame é nulo
     if (!exam){
        fprintf(stderr, "Error: NULL exam pointer");
        return 1;
     }

    return(exam->id);
}

const int exam_get_patient_id(Exam *exam){
    /** \brief This function gets and returns the unique identification of the patient
     *         associated with the exam // Esta função obtém e retorna a identificação
     *         única do paciente associado ao exame
     *
     * \param exam - Pointer to exam's structure // Ponteiro para a estrutura do exame
     * \return The patient's ID // O ID do paciente
     *
     * \details This function retrieves the unique identification number of the patient associated with the exam.
     *          It checks if the exam pointer is NULL. If it is NULL, an error message is printed to stderr and
     *          the function returns 1.
     * \details Esta função recupera o número de identificação único do paciente associado ao exame.
     *          Ela verifica se o ponteiro exam é NULL. Se for NULL, uma mensagem de erro é impressa em stderr e
     *          a função retorna 1.
     *
     * \warning If the exam pointer is NULL, this function prints an error message to stderr and returns 1.
     *          Se o ponteiro exam for NULL, esta função imprime uma mensagem de erro em stderr e retorna 1.
     */

     // Checks if the exam pointer is NULL
     // Verifica se o ponteiro do exame é nulo
     if (!exam){
        fprintf(stderr, "Error: NULL exam pointer");
        return 1;
     }

    return(exam->patient_id);
}

const int exam_get_rx_id(Exam *exam){
    /** \brief This function gets and returns the unique identification of the x-ray machine
     *         Esta função obtém e retorna a identificação única do aparelho de raio x
     *
     * \param exam - Pointer to exam's structure // Ponteiro para a estrutura do exame
     * \return The x-ray ID // O ID do raio x
     *
     * \details This function retrieves the unique identification number of the x-ray machine associated with the exam.
     *          It checks if the exam pointer is NULL. If it is NULL, an error message is printed to stderr and
     *          the function returns 1.
     * \details Esta função recupera o número de identificação único do aparelho de raio x associado ao exame.
     *          Ela verifica se o ponteiro exam é NULL. Se for NULL, uma mensagem de erro é impressa em stderr e
     *          a função retorna 1.
     *
     * \warning If the exam pointer is NULL, this function prints an error message to stderr and returns 1.
     *          Se o ponteiro exam for NULL, esta função imprime uma mensagem de erro em stderr e retorna 1.
     */

     // Checks if the exam pointer is NULL
     // Verifica se o ponteiro do exame é nulo
     if (!exam){
        fprintf(stderr, "Error: NULL exam pointer");
        return 1;
     }

    return(exam->rx_id);
}

const char *exam_get_condition(Exam *exam){
    /** \brief This function gets and returns the unique identification of the x-ray machine
     *         Esta função obtém e retorna a identificação única do aparelho de raio x
     *
     * \param exam - Pointer to exam's structure // Ponteiro para a estrutura do exame
     * \return The x-ray ID // O ID do raio x
     *
     * \details This function retrieves the unique identification number of the x-ray machine associated with the exam.
     *          It checks if the exam pointer is NULL. If it is NULL, an error message is printed to stderr and
     *          the function returns 1.
     * \details Esta função recupera o número de identificação único do aparelho de raio x associado ao exame.
     *          Ela verifica se o ponteiro exam é NULL. Se for NULL, uma mensagem de erro é impressa em stderr e
     *          a função retorna 1.
     *
     * \warning If the exam pointer is NULL, this function prints an error message to stderr and returns 1.
     *          Se o ponteiro exam for NULL, esta função imprime uma mensagem de erro em stderr e retorna 1.
     */

     // Checks if the exam pointer is NULL
     // Verifica se o ponteiro do exame é nulo
     if (!exam){
        fprintf(stderr, "Error: NULL exam pointer");
        return 1;
     }

    return(exam->condition_ia);
}

const int exam_get_time(Exam *exam){
    /** \brief This function gets and returns the exam time // Esta função obtém e retorna o horário
     *         de realização do exame
     *
     * \param exam - Pointer to exam's structure // Ponteiro para a estrutura do exame
     * \return The exam time // O horário do exame
     *
     * \details This function retrieves the time at which the exam was conducted.
     *          It checks if the exam pointer is NULL. If it is NULL, an error message is printed to stderr and
     *          the function returns NULL.
     * \details Esta função recupera o horário em que o exame foi realizado.
     *          Ela verifica se o ponteiro exam é NULL. Se for NULL, uma mensagem de erro é impressa em stderr e
     *          a função retorna NULL.
     *
     * \warning If the exam pointer is NULL, this function prints an error message to stderr and returns NULL.
     *          Se o ponteiro exam for NULL, esta função imprime uma mensagem de erro em stderr e retorna NULL.
     */

     // Checks if the exam pointer is NULL
     // Verifica se o ponteiro do exame é nulo
     if (!exam){
        fprintf(stderr, "Error: NULL exam pointer");
        return 1;
     }

    return(exam->time);
}


// SETTERS

void exam_set_id(Exam *exam, int id) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    exam->id = id;
}

void exam_set_patient_id(Exam *exam, int patient_id) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    exam->patient_id = patient_id;
}

void exam_set_rx_id(Exam *exam, int rx_id) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    exam->rx_id = rx_id;
}

void exam_set_condition(Exam *exam, char *condition_ia) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    exam->condition_ia = condition_ia;
}

void exam_set_time(Exam *exam, int time) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    exam->time = time;
}

const void exam_save(Exam*exam, const char *file_name, const char *str) {
    /** \brief Saves a string representation of the exam to a file.
     *
     * \param exam - Pointer to the Exam object. This parameter is not used in this function but is included for consistency with other functions.
     * \param file_name - The name of the file where the exam information will be saved.
     * \param str - The string representation of the exam to be saved in the file.
     *
     * \details This function creates a FileHandler for the specified file, writes the provided string to the file, and then
     *          destroys the FileHandler. The function does not perform any checks on the validity of the input parameters.
     * \details Esta função cria um manipulador de arquivos para o arquivo especificado, escreve a string fornecida no arquivo e
     *          depois destrói o manipulador de arquivos. A função não realiza verificações sobre a validade dos parâmetros de entrada.
     *
     * \warning Ensure that the file_name and str parameters are valid and that file_name points to a writable location.
     * \warning Certifique-se de que os parâmetros file_name e str são válidos e que file_name aponte para um local gravável.
     */

    // Builds the file handler
    // Constrói o manipulador de arquivos
    FileHandler *fh = fh_create(file_name);

    fh_write(fh, str);
    fh_destroyer(fh);
}

