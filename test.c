#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct 
{
    char name[50];
    int height;
    double mass;
    char hair_color[50];
    char skin_color[50];
    char eye_color[50];
    char birth_year[50];
    char gender[50];
    char homeworld[50];
}Character;

Character create_char(char* archive);
void populate_list(Character* list, char (*archives)[200], int* length);
int treat_command(char command0, char command1);
void insereInicio(Character* list, Character p, int* length);
void inserir(Character* list, int posicao, Character p, int* length);
void inserirFim(Character* list, Character p, int* length);
void removerInicio(Character* list, int* length);
void remover(Character* list, int position, int* length);
void removerFim(Character* list, int* length);
void printCharacteristics(Character character);


int main(){
    char inputs[1000][200];
    char commands[1000][200];
    bool flag = true;
    int counter = 0, steps;
    while(flag){
        scanf("%s", inputs[counter]);
        if(strlen(inputs[counter]) == 3 && inputs[counter][0] == 'F'
        && inputs[counter][1] == 'I' && inputs[counter][2] == 'M'){
            break;
        }
        counter++;
    }
    scanf("%d", &steps);
    for(int i = 0; i < steps ; i++){
        scanf("%s", commands[i]);
    }

    Character* list = (Character*) malloc(counter*sizeof(Character));

    populate_list(list, inputs, &counter);
    int cmd_exec = -1;
    int position;
    //execute the commands
    for(int i = 0; i < steps ; i++){
        cmd_exec = treat_command(commands[i][0],commands[i][1]);
        if(cmd_exec == 0){
            insereInicio(list, create_char(commands[i]),&counter);
        }else if(cmd_exec == 1){
            inserirFim(list, create_char(commands[i]), &counter);
        }else if(cmd_exec == 2){ 
            sscanf(commands[i], "I* %d", &position);
            inserir(list, position, create_char(commands[i]), &counter);
        }else if(cmd_exec==3){
            printf("(R) %s", list[0].name);
            removerInicio(list,&counter);
        }else if(cmd_exec == 4){
            printf("(R) %s", list[counter].name);
            removerFim(list, &counter);
        }else if(cmd_exec == 5){
            sscanf(commands[i], "R* %d", &position);
            printf("(R) %s", list[position].name);
            remover(list, position, &counter);
        }else{
            printf("problema na entrada");
        }
    }
    
    for(int i = 0; i < counter; i++){
        printCharacteristics(list[i]);
    }

    free(list);

    return 0;
}

Character create_char(char* archive){
    char aux_path [200];
    int i;
    for(i = 0 ; archive[i] != '\0' ; i++){
        if(archive[i]=='\\'){
            break;
        }
    }
    for(int j = 0; archive[i] != '\0' ; i++, j++){
        aux_path[j] = archive[i];
    }
    ///////////
    // for(i = 3; archive[i] != '\0'; i++){
    //     aux_path[i - 3] = archive[i];
    // }
    // aux_path[i - 3] = '\0';
    /////////
    Character aux;
    printf("%s\n",aux_path);
    FILE *fp = fopen(aux_path, "r");
    if (fp == NULL) {
        printf("Error: could not open file\n");
        exit(0);
    }
    fscanf(fp, "{'name': \'%s\', 'height': \'%d\', 'mass': \'%lf\', 'hair_color': \'%s\', 'skin_color': \'%s\', 'eye_color': \'%s\', 'birth_year': \'%s\', 'gender': \'%s\', 'homeworld': \'%s\'", aux.name, &aux.height, &aux.mass, aux.skin_color,
    aux.eye_color, aux.birth_year, aux.gender, aux.homeworld);
    fclose(fp);
    return aux;
}

void populate_list(Character* list, char (*archives)[200], int* length){
    for(int i = 0; i < *length; i++){
        FILE *fp = fopen(archives[i], "r");
        if (fp == NULL) {
            printf("Error: could not open file\n");
            exit(0);
        }
        fscanf(fp, "{'name': \'%s\', 'height': \'%d\', 'mass': \'%lf\', 'hair_color': \'%s\', 'skin_color': \'%s\', 'eye_color': \'%s\', 'birth_year': \'%s\', 'gender': \'%s\', 'homeworld': \'%s\'", list[i].name, list[i].height, list[i].mass, list[i].skin_color,
         list[i].eye_color, list[i].birth_year, list[i].gender, list[i].homeworld);
        fclose(fp);
    }
}

int treat_command(char command0, char command1){
    int operation;
    if(command0 == 'I' && command1 == 'I'){
        operation = 0;
    }else if(command0 == 'I' && command1 == 'F'){
        operation = 1;
    }else if(command0 == 'I' && command1 == '*'){
        operation = 2;
    }else if(command0 == 'R' && command1 == 'I'){
        operation = 3;
    }else if(command0 == 'R' && command1 == 'F'){
        operation = 4;
    }else if(command0 == 'R' && command1 == '*'){
        operation = 5;
    }else{
        operation = -1;
    }
    return operation;
}


void insereInicio(Character* list, Character p, int* length){
    (*length) = (*length) + 1;
    Character* temp = (Character*) realloc(list, (*length)*sizeof(Character));
     if (temp == NULL) {
        printf("Memory reallocation failed.\n");
        free(list);
    } else {
        list = temp;
        for(int i=(*length)-1; i >= 0 ; i--){
            list[i] = list[i-1];
        }
        list[0] = p;
    }

}

void inserir(Character* list, int posicao, Character p, int* length){
    (*length) = (*length) + 1;
    Character* temp = (Character*) realloc(list, (*length)*sizeof(Character));
     if (temp == NULL) {
        printf("Memory reallocation failed.\n");
        free(list);
    } else {
        list = temp;
        for(int i= (*length) - 1 ; i > (*length) ; i--){
            list[i] = list[i-1];
        }
        list[posicao] = p;
    }
}

void inserirFim(Character* list, Character p, int* length){
    (*length) = (*length) + 1;
    Character* temp = (Character*) realloc(list, (*length)*sizeof(Character));
     if (temp == NULL) {
        printf("Memory reallocation failed.\n");
        free(list);
    } else {
        list = temp;
        list[(*length)-1] = p; 
    }
}

void removerInicio(Character* list, int* length){
    (*length) = (*length) - 1;
    Character* temp = (Character*) realloc(list, (*length)*sizeof(Character));
    if (temp == NULL) {
        printf("Memory reallocation failed.\n");
        free(list);
    }else{
        for(int i = 0; i<(*length)+1;i++){
            list[i] = list[i+1];
        }
        list = temp;
    }
}

void remover(Character* list, int position, int* length){
    (*length) = (*length) - 1;
    Character* temp = (Character*) realloc(list, (*length)*sizeof(Character));
    if (temp == NULL) {
        printf("Memory reallocation failed.\n");
        free(list);
    }else{
        for(int i = position; i < (*length) ; i++){
            list[i] = list[i+1];
        }
        list = temp;
    }
}

void removerFim(Character* list, int* length){
    (*length) = (*length) - 1;
    Character* temp = (Character*) realloc(list, (*length)*sizeof(Character));
    if (temp == NULL) {
        printf("Memory reallocation failed.\n");
        free(list);
    }else{
        list = temp;
    }
}

void printCharacteristics(Character character){

    printf("## ");
    printf("%s", character.name);
    printf(" #");

    printf("# ");
    printf("%i", character.height);
    printf(" #");

    printf("# ");
    printf("%lf", character.mass);
    printf(" #");

    printf("# ");
    printf("%s", character.hair_color);
    printf(" #");

    printf("# ");
    printf("%s", character.skin_color);
    printf(" #");

    printf("# ");
    printf("%s", character.eye_color);
    printf(" #");

    printf("# ");
    printf("%s", character.birth_year);
    printf(" #");

    printf("# ");
    printf("%s", character.gender);
    printf(" #");

    printf("# ");
    printf("%s", character.homeworld);
    printf(" #");

}
