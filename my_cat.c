#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    FILE *fp, *lt;
    char c, text[10000];
    int i;

    if(argc < 2){                                                                       // Uso incorrecto
        printf("Uso incorrecto del programa: ./a.out <nombre de archivo>");
        exit(0);
    }

    for(i = 1; i < argc; i++){                                                          // Guardado en archivo (Uso de opción -o)
        if(strcmp(argv[argc - 2], "-o") == 0){
            lt = fopen(argv[argc - 1], "w");
            for(i = 1; i < argc - 2; i++){
                fp = fopen(argv[i], "r");
                while(1){
                    c = fgetc(fp);
                    if( feof(fp)){
                        break;
                    }
                    fputc(c,lt);
                }
                fclose(fp);
            }
            fclose(lt);
            exit(0);
        }
    }

    for(i = 1; i < argc; i++){                                                         // Impresión en pantalla
        fp = fopen(argv[i], "r");
        while(1){
            c = fgetc(fp);
            if( feof(fp)){
                break;
            }
            printf("%c", c);
        }
        fclose(fp);
    }

    return 0;
}
