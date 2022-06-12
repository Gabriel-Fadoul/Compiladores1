#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_intruction(char *line){
    if(strstr(line,"LOAD") != NULL){
        printf("01");
    }
    if(strstr(line,"STORE") != NULL){
        printf("02");
    }
    if(strstr(line,"ADD") != NULL){
        printf("03");
    }
    if(strstr(line,"SUB") != NULL){
        printf("04");
    }
    if(strstr(line,"JMP") != NULL){
        printf("05");
    }
    if(strstr(line,"JPG") != NULL){
        printf("06");
    }
    if(strstr(line,"JPL") != NULL){
        printf("07");
    }
    if(strstr(line,"JPE") != NULL){
        printf("08");
    }
    if(strstr(line,"JPNE") != NULL){
        printf("09");
    }
    if(strstr(line,"PUSH") != NULL){
        printf("10");
    }
    if(strstr(line,"POP") != NULL){
        printf("11");
    }
    if(strstr(line,"READ") != NULL){
        printf("12");
    }
    if(strstr(line,"WRITE") != NULL){
        printf("13");
    }
    if(strstr(line,"CALL") != NULL){
        printf("14");
    }
    if(strstr(line,"RET") != NULL){
        printf("15");
    }
    if(strstr(line,"HALT") != NULL){
        printf("16");
    }
    else{
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
