/*
 * cat
 *
 * Versione: 1.0
 * Autore: Andre Valenzano
 * Data: 28-10-2020
 *
 * Programma per concatenare FILE(s) sullo standard output
 * In caso di assenza di FILE legge dallo standard input
 *
 * Programma creato durante il corso di Sistemi di Elaborazione e
 * Trasmissione dell'Informazione presso l'Università degli Studi di Genova,
 * anno accademico 2020/2021
 *
 */

/**** Includo le librerie ****/
#include <stdio.h> /* perror */
#include <stdlib.h> /* exit */
#include <string.h> /* strcmp */
#include <unistd.h> /* read, write*/
#include <sys/types.h> /*       */
#include <sys/stat.h> /* open  */
#include <fcntl.h>   /*       */
#include <errno.h>

/**** Definisco le variabili globali ****/
#define STDIN 0 /* STDIN File Descriptor */
#define STDOUT 1 /* STDOUT File Descriptor */
#define STDERR 2 /* STDERR File Descriptor */

#define STDIN_BUFF_SIZE 1024 /* 1 KiB */
#define FILE_BUFF_SIZE 4096 /* 4 MiB */

int main(int argc, char** argv){

/**** Nel caso in cui non specifico un FILE negli argomenti, leggo da STDIN ****/
    if(argc == 1){

        char BUFF[STDIN_BUFF_SIZE];
        ssize_t read_bytes;

        for(;;){
            if((read_bytes = read(STDIN, BUFF, STDIN_BUFF_SIZE)) == -1){
                /* Se non riesco a leggere dallo standard input, esco dal programma riportando il messaggio di errore*/
                perror("Can't read thrue STDIN");
                exit(EXIT_FAILURE);
            }
            if((write(STDOUT, BUFF, read_bytes)) == -1){
                /* Se non riesco a scrivere sullo standard output, esco dal programma riportando il messaggio di errore*/
                perror("Can't write to STDOUT");
                exit(EXIT_FAILURE);
            }
        }
    }

/**** Altrimenti leggo da FILE, nel caso di più parametri concateno il contenuto dei vari FILEs ****/
    else{
        /**** Firma dell'autore ****/
        if((strcmp(argv[1],"mother_of_all_questions")) == 0){
            goto mother_of_all_questions;
        }

        /**** Apro i vari FILEs dati come argomento e li concateno su standard output****/
        int file_fd;
        char* BUFF = malloc(FILE_BUFF_SIZE);
        ssize_t read_bytes;
        size_t total_bytes = 0;
        size_t buff_size = FILE_BUFF_SIZE;

        for(unsigned int i = 1; i < argc; i++){
            if((file_fd = open(argv[i], O_RDONLY)) == -1){
                /* Se non riesco ad aprire il FILE, esco dal programma riportanndo il messaggio di errore*/
                perror(argv[i]);
                close(file_fd);
                exit(EXIT_FAILURE);
            }
read_:
            if((read_bytes = read(file_fd, (BUFF + total_bytes), (buff_size - total_bytes))) == -1){
                /* Se non riesco a leggere da FILE, esco dal programma riportanndo il messaggio di errore*/
                perror("Can't read thrue FD");
                close(file_fd);
                exit(EXIT_FAILURE);
            }
            total_bytes += read_bytes;

            if(buff_size == total_bytes){
                buff_size += FILE_BUFF_SIZE;
                BUFF = realloc(BUFF, buff_size);
                goto read_;
            }

            close(file_fd);
        }

        if((write(STDOUT, BUFF, total_bytes)) == -1){
            /* Se non riesco a scrivere sullo standard output, esco dal programma riportando il messaggio di errore*/
            perror("Can't write to STDOUT");
            exit(EXIT_FAILURE);
        }

        free(BUFF);
    }

exit(EXIT_SUCCESS);

mother_of_all_questions:
    if((write(STDOUT, "\n\tFoto Piedi?\n\n", 15)) == -1){
        /* Se non riesco a scrivere sullo standard output, esco dal programma riportando il messaggio di errore*/
        perror("Can't write to STDOUT");
        exit(EXIT_FAILURE);
    }
exit(EXIT_SUCCESS);
}













