#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_intruction(char *line){
    if(strstr(line,"LOAD") != NULL){
        printf("01");
    }else{
        printf("%s",line);
    }
}

int main(){
    FILE* arq;
    char* read;
    char* tok;
    char instruction[100];
    arq = fopen("teste","rt");
    int PC = 0;
    while(!feof(arq)){
        read = fgets(instruction, 100, arq);
        if(read){
            //printf("Linha %d: %s", PC, instruction);
            tok = strtok(instruction," ");
            if(tok != NULL && strstr(tok,":") == NULL){ // Caso não seja uma label
                check_intruction(tok);
                tok = strtok (NULL, " ");
                printf(" %s",tok);
            }
        }
        PC++;
    }
    fclose(arq);
    return 0;
}
