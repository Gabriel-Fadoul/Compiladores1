#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char symbol;
    int value;
} Data;

int check_intruction(char *line, FILE* out){
    if(strstr(line,"LOAD") != NULL){
        fprintf(out,"1 ");
    }
    if(strstr(line,"STORE") != NULL){
        fprintf(out,"2 ");
    }
    if(strstr(line,"ADD") != NULL){
        fprintf(out,"3 ");
    }
    if(strstr(line,"SUB") != NULL){
        fprintf(out,"4 ");
    }
    if(strstr(line,"JMP") != NULL){
        fprintf(out,"5 ");
    }
    if(strstr(line,"JPG") != NULL){
        fprintf(out,"6 ");
    }
    if(strstr(line,"JPL") != NULL){
        fprintf(out,"7 ");
    }
    if(strstr(line,"JPE") != NULL){
        fprintf(out,"8 ");
    }
    if(strstr(line,"JPNE") != NULL){
        fprintf(out,"9 ");
    }
    if(strstr(line,"PUSH") != NULL){
        fprintf(out,"10 ");
    }
    if(strstr(line,"POP") != NULL){
        fprintf(out,"11 ");
    }
    if(strstr(line,"READ") != NULL){
        fprintf(out,"12 ");
    }
    if(strstr(line,"WRITE") != NULL){
        fprintf(out,"13 ");
    }
    if(strstr(line,"CALL") != NULL){
        fprintf(out,"14 ");
    }
    if(strstr(line,"RET") != NULL){
        fprintf(out,"15 ");
        return 1;
    }
    if(strstr(line,"HALT") != NULL){
        fprintf(out,"16 ");
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
    if(strstr(line,"END") == NULL && strstr(line,"WORD") == NULL && strstr(line,"RET") == NULL && strstr(line,"HALT") == NULL && strstr(line,":") == NULL){
        (*pos_counter) += 2;
    
    //se for RET/HALT/WORD conta apenas 1
    } else if(strstr(line,":") == NULL && strstr(line,"END") == NULL){
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

int main(int argc, char *argv[]){
    FILE* arq;
    char *read, *tok2, *op, *opn;
    Data data[1000];
    char instruction[100];
    arq = fopen(argv[1],"rt");

    int symbol_counter = 0; // registra a quantidade de simbolos
    int pos_counter = 0; // registra a posicao

    while(!feof(arq)){
        read = fgets(instruction, 100, arq);
        if(read){
            tok2 = strtok(instruction," ");
            if(tok2 != NULL){
                //check_intruction(tok2, &pos_counter, PC);
                add_symbol(tok2, data, &symbol_counter, &pos_counter);
                if(strstr(tok2,":") != NULL){
                    tok2 = strtok (NULL, " ");
                }
                update_ilc(tok2,&pos_counter);
            }
        }
    }
    fclose(arq);

    arq = fopen(argv[1],"rt");
    FILE* output = fopen(argv[2],"wt");

    fprintf(output,"MV1 0 999 %d ",pos_counter);


    int pos_symbol;
    pos_counter = 0;

    while(!feof(arq)){
        read = fgets(instruction, 100, arq);
        if(read){          
            tok2 = strtok(instruction," ");
            if(tok2 != NULL){
                // L: WRITE A
                if(strstr(tok2,":") == NULL){ //Não é label
                    op = tok2; //Operador
                    opn = strtok (NULL, " "); //Operando

                }else{ //É label
                    op  = strtok(NULL, " "); //Operador
                    opn = strtok(NULL, " "); //Operando
                }
                
                if(check_intruction(op,output) == 0){                    
                    
                    update_ilc(op,&pos_counter);
                    check_data(data, symbol_counter, *opn, &pos_symbol);
                    fprintf(output,"%d ", pos_symbol-pos_counter);

                }else if(strstr(op,"WORD") != NULL){
                    fprintf(output,"%c ",*opn);
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
