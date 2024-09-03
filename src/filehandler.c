#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/filehandler.h"

#define MAX_FILENAME_CHAR 45

struct file_handler {
    FILE *file;
    char *file_name;
};


// Private functions signatures
// Asinaturas das funções privadas
static void _fh_open(FileHandler *handler, const char *file_name, const char *mode);



// PUBLIC FUNCTIONS // FUNÇÕES PÚBLICAS


FileHandler *fh_create(const char *file_name) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */

    // Allocates memory for file handler structure
    // Aloca memória para a estrutura manipulador de arquivos
    FileHandler *handler = (FileHandler *) malloc(sizeof(FileHandler));

    // Checks if allocation was successful
    // Verifica se a alocação foi bem sucedida
    if (!handler) {
        fprintf(stderr, "Error: building file handler failure \n");
        return NULL;
    }

    // Allocates memory for file name
    // Aloca memória para nome do arquivos
    handler->file_name = (char *) calloc(MAX_FILENAME_CHAR, sizeof(char));

    // Checks if allocation was successful
    // Verifica se a alocação foi bem sucedida
    if (!handler->file_name) {
        fprintf(stderr, "Error: building file name failure \n");
        fh_destroyer(handler);
        return NULL;
    }

    // Copy the provided file name to the allocated memory
    // Copia o nome do arquivo fornecido para a memória alocada
    strcpy(handler->file_name, file_name);

    return handler;
}

int fh_is_open(FileHandler *handler) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    return (handler && handler->file);
}

void fh_write(FileHandler *handler, const char *str) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if the handler exist
    // Verifica se o manipulador existe
    if (!handler) {
        fprintf(stderr, "Error: the handler is null \n");
    }

    if (fh_is_open(handler)) {
        fprintf(handler->file, str);
        fprintf(handler->file, "\n\n");
    } else {
        _fh_open(handler, handler->file_name, "w");

        fprintf(handler->file, str);
        fprintf(handler->file, "\n\n");
    }
}

void fh_destroyer(FileHandler *handler) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if the handler exist
    // Verifica se o manipulador existe
    if (!handler) {
        fprintf(stderr, "Error: the handler is null \n");
        return;
    }

    // Checks if the file exist and is opened
    // Verifica se o arquivo existe e está aberto
    if (handler->file && fh_is_open(handler)) {
        fclose(handler->file);
    }

    free(handler);
}



// PRIVATE FUNCTIONS // FUNÇÕES PRIVADAS


static void _fh_open(FileHandler *handler, const char *file_name, const char *mode) {
    /** \brief
     *
     * \param
     * \param
     * \return
     *
     */


    // Checks if handler exist
    // Verifica se o manipulador existe
    if (!handler) {
        fprintf(stderr, "Error: handler is NULL \n");
        return;
    }

    // Opens the file
    // Abre o arquivo
    handler->file = fopen(file_name, mode);

    // Checks if the file has been opened
    // Verifica se o arquivo foi aberto
    if(!handler->file) {
        fprintf(stderr, "Error: unable to open file '%s'\n", file_name);
        return;
    }
}
