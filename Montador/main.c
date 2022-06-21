#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int PC = 1;
int AC = 0;
int SP = 999;

int pass_one(FILE* arq){
    return 0;
}

typedef struct {
    char symbol;
    int value;
} Data;

int check_intruction(char *line){
    if(strstr(line,"LOAD") != NULL){
        printf("1 ");
    }
    if(strstr(line,"STORE") != NULL){
        printf("2 ");
    }
    if(strstr(line,"ADD") != NULL){
        printf("3 ");
    }
    if(strstr(line,"SUB") != NULL){
        printf("4 ");
    }
    if(strstr(line,"JMP") != NULL){
        printf("5 ");
    }
    if(strstr(line,"JPG") != NULL){
        printf("6 ");
    }
    if(strstr(line,"JPL") != NULL){
        printf("7 ");
    }
    if(strstr(line,"JPE") != NULL){
        printf("8 ");
    }
    if(strstr(line,"JPNE") != NULL){
        printf("9 ");
    }
    if(strstr(line,"PUSH") != NULL){
        printf("10 ");
    }
    if(strstr(line,"POP") != NULL){
        printf("11 ");
    }
    if(strstr(line,"READ") != NULL){
        printf("12 ");
    }
    if(strstr(line,"WRITE") != NULL){
        printf("13 ");
    }
    if(strstr(line,"CALL") != NULL){
        printf("14 ");
    }
    if(strstr(line,"RET") != NULL){
        printf("15 ");
        return 1;
    }
    if(strstr(line,"HALT") != NULL){
        printf("16 ");
        return 1;
    }
    if(strstr(line,"WORD") != NULL || strstr(line,"END") != NULL){
        return 1;
    }
    return 0;
}

//atualiza posição da memória
void update_ilc(char* line, int* pos_counter){
    //se nao for RET/HALT conta 2, pois esses comandos contam como 1
    if(strstr(line,"WORD") == NULL && strstr(line,"RET") == NULL && strstr(line,"HALT") == NULL && strstr(line,":") == NULL){
        (*pos_counter) += 2;
    
    //se for RET/HALT/WORD conta apenas 1
    } else if(strstr(line,":") == NULL){
        (*pos_counter) ++;
    }
}

//verifica se o simbolo ja foi registrado
int check_data(Data data[], int symbol_counter, char symbol, int* catch) {
    for(int i = 0; i < symbol_counter; i++) {
        if(data[i].symbol == symbol) {
            if (catch != NULL){
                *catch = data[i].value;
            }
            return 0;
        }
    }
    return 1;
}

void add_symbol(char *line, Data data[], int* symbol_counter, int* pos_counter) {
    //caso tenha :
    if(strstr(line,":") != NULL){
        (*pos_counter)++; //incrementa o contador (ele nao sera incrementado na check_intruction)
        if(check_data(data, *symbol_counter, line[0],NULL)) { //verifica se o simbolo ja nao esta presente na lista
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
    char *read, *tok2, *op, *opn;
    Data data[1000];
    char instruction[100];
    arq = fopen("teste","rt");

    int symbol_counter = 0; // registra a quantidade de simbolos
    int pos_counter = 0; // registra a posicao

    while(!feof(arq)){
        read = fgets(instruction, 100, arq);
        if(read){
            PC++;
            tok2 = strtok(instruction," ");
            if(tok2 != NULL){
                //check_intruction(tok2, &pos_counter, PC);
                update_ilc(tok2,&pos_counter);
                add_symbol(tok2, data, &symbol_counter, &pos_counter);
                tok2 = strtok (NULL, " ");
            }
        }
    }
    fclose(arq);
    arq = fopen("teste","rt");
    int pos_symbol;
    pos_counter = 0;

    while(!feof(arq)){
        read = fgets(instruction, 100, arq);
        if(read){          
            tok2 = strtok(instruction," ");
            if(tok2 != NULL){
                if(strstr(tok2,":") == NULL){ //Não é label
                    op = tok2; //Operador
                    opn = strtok (NULL, " "); //Operando

                }else{ //É label
                    op  = strtok(NULL, " "); //Operador
                    opn = strtok(NULL, " "); //Operando
                }
                if(check_intruction(op) == 0){                    
                    
                    update_ilc(op,&pos_counter);
                    check_data(data, symbol_counter, *opn, &pos_symbol);
                    printf("%d ", pos_symbol-pos_counter);
                }else if(strstr(op,"WORD") != NULL){
                    printf("%c ",*opn);
                    update_ilc(op,&pos_counter);
                }
                else{
                    update_ilc(op,&pos_counter);
                }
            }
        }
    }
    fclose(arq);
    return 0;
}
