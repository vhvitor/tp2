#ifndef FILEHANDLER_H_INCLUDED
#define FILEHANDLER_H_INCLUDED

// File handler structure
// Estrutura manipulador de arquivos
typedef struct file_handler FileHandler;

// Creates a file structure
// Cria um arquivo
FileHandler *fh_create(const char *file_name);

// Opens a file with the specified mode
// Abre um arquivo com mo modo especificado
FileHandler *fh_open(const char *filename, const char *mode);

// Writes data to file
// Escreve dados no arquivo
void fh_write(FileHandler *handler, const char *str);

// File Handler destroyer
// Destrutor do manipulador de arquivos
void fh_destroyer(FileHandler *handler);

#endif // FILEHANDLER_H_INCLUDED
