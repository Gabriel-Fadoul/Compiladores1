#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_intruction(char *line, int* pos_counter, int PC){
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
    //se nao for RET/HALT conta 2, pois esses comandos contam como 1
    if(strstr(line,"RET") == NULL && strstr(line,"HALT") == NULL && strstr(line,":") == NULL){
        (*pos_counter) += 2;
    
    //se for RET/HALT conta apenas 1
    } else if(strstr(line,":") == NULL) {
        (*pos_counter) ++;
    }
}

typedef struct {
    char symbol;
    int value;
} Data;

//verifica se o simbolo ja foi registrado
int check_data(Data data[], int symbol_counter, char symbol) {
    for(int i = 0; i < symbol_counter; i++) {
        if(data[i].symbol == symbol) {
            return 0;
        }
    }
    return 1;
}

void add_symbol(char *line, Data data[], int* symbol_counter, int* pos_counter) {
    //caso tenha :
    if(strstr(line,":") != NULL){
        (*pos_counter)++; //incrementa o contador (ele nao sera incrementado na check_intruction)
        if(check_data(data, *symbol_counter, line[0])) { //verifica se o simbolo ja nao esta presente na lista
            data[*symbol_counter].symbol = line[0]; // salva simbolo
            data[*symbol_counter].value = *pos_counter; // salva posicao
            (*symbol_counter)++; //registra o aparecimento de simbolo
        }
    }
}

void print_data(Data data[], int count) {
    for(int i = 0; i < count; i++) {
       printf("\npos: %d\n",data[i].value);
       printf("symbol: %c\n",data[i].symbol);
    }
}

int main(){
    FILE* arq;
    char* read;
    char* tok;
    char instruction[100];
    arq = fopen("teste","rt");
    int PC = 1;
    
    Data data[1000];
    int symbol_counter = 0; // registra a quantidade de simbolos
    int pos_counter = 0; // registra a posicao
    char* tok2;

    while(!feof(arq)){
        read = fgets(instruction, 100, arq);
        if(read){
            PC++;
            // printf("Linha %d: %s", PC, instruction);
            // tok = strtok(instruction," ");
            // if(tok != NULL && strstr(tok,":") == NULL){ // Caso não seja uma label
            //     check_intruction(tok, (0), PC);
            //     tok = strtok (NULL, " ");
            //     printf(" %s",tok);
            // }
            
            tok2 = strtok(instruction," ");
            if(tok2 != NULL){ 
                check_intruction(tok2, &pos_counter, PC);
                add_symbol(tok2, data, &symbol_counter, &pos_counter);
                tok2 = strtok (NULL, " ");
                printf(" %s",tok2);
            }
        }
    }
    print_data(data, symbol_counter);
    fclose(arq);
    return 0;
}
