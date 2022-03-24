#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include  <conio.h>

struct driver{                                                                                                          //declar struct driver
    char name[50];
    char number[5];
    char team[50];
    char gpwin[5];
    char time[10];
};

void menu();                                                                                                            //declar functiile pentru a le putea apela mai departe in cod
void addRecord();
void rankRecord();
void searchRecord();
void editRecord();
void deleteRecord();


void menu(){                                                                                                            //meniul aplicatiei
    system("cls");                                                                                             //apelez system pentru a executa "cls" care curata consola
    printf("\n\t\t*****F1 Database*****");
    printf("\n\n\t\t  MENU\t\t\n\n");
    printf("\t1.Add New Pilot   \n\t2.List of Pilots   \n\t3.Search  \n\t4.Edit \n\t5.Delete \n\t6.Exit");

    switch(getch()){                                                                                                    //switch case in care executi o anumita functie alegand unul dintre numere
        case '1': addRecord();
            break;
        case '2': rankRecord();
            break;
        case '3': searchRecord();
            break;
        case '4': editRecord();
            break;
        case '5': deleteRecord();
            break;
        case '6': exit(0);
            break;
        default:
            system("cls");
            printf("\n\tEnter a number from 1 to 6:");
            getch();
            menu();
    }
}

void addRecord (){                                                                                                      //functia pe care o folosim pentru a adauga un pilot in lista
    system("cls");
    FILE *f;                                                                                                            //pointerul catre fisier
    struct driver p;
    f=fopen("data.txt","a+");
    printf("\tWrite pilot name:\n");
    fgets(p.name, 50, stdin);
    strtok(p.name, "\n");
    printf("\tWrite pilot number:\n");
    fgets(p.number, 5, stdin);
    strtok(p.number, "\n");
    printf("\tWrite pilot team:\n");
    fgets(p.team, 50, stdin);
    strtok(p.team, "\n");
    printf("\tWrite pilot number of wins:\n");
    fgets(p.gpwin, 5, stdin);
    strtok(p.gpwin, "\n");
    printf("\tWrite pilot best time:\n");
    fgets(p.time, 15, stdin);
    strtok(p.time, "\n");
    fwrite(&p,sizeof(p),1,f);
    printf("\n\t\tRecord saved");
    printf("\n\tName:%s\n\tNumber:%s\n\tTeam:%s\n\tWins:%s\n\tTime:%s\n", p.name, p.number,p.team,p.gpwin,p.time);
    fclose(f);
    printf("\nEnter any key to go back");
    getch();
    system("cls");
    menu();
}

void rankRecord(){                                                                                                      //functia care ne arata lista cu toti pilotii in ordinea in care i am introdus
    system("cls");
    struct driver p;
    FILE *f;
    f=fopen("data.txt","r+");
    if (f==NULL){
        printf("\n\tFile opening error");
        exit(1);
    }
    while (fread(&p, sizeof(p),1,f)==1){
        printf("\n\tName:%s\n\tNumber:%s\n\tTeam:%s\n\tWins:%s\n\tTime:%s\n", p.name, p.number,p.team,p.gpwin,p.time);
    }
    fclose(f);
    printf("\nEnter any key to go back");
    getch();
    system("cls");
    menu();
}

void searchRecord(){                                                                                                    //functie pentru a cauta un pilot dupa nume
    system("cls");
    struct driver p;
    FILE *f;
    char name[50];
    f=fopen("data.txt","r+");
    if (f==NULL){
        printf("\nFile opening error");
        exit(1);
    }
    printf("\n\tSearch for pilot name:");
    fgets(name,50,stdin);
    strtok(name, "\n");
    while (fread(&p,sizeof(p),1,f)==1){
        if (strcmp(p.name, name)==0){
            printf("\n\t\tPilot you searched for:");
            printf("\n\tName:%s\n\tNumber:%s\n\tTeam:%s\n\tWins:%s\n\tTime:%s\n", p.name, p.number,p.team,p.gpwin,p.time);
        }
        else
            printf("\nnot found\nPress 1 to search again or 2 to go back");

        switch(getch()){
            case '1':searchRecord();
                break;
            case '2':menu();
        }
    }
    fclose(f);
    printf("\nEnter any key to go back");
    getch();
    system("cls");
    menu();
}

void editRecord(){                                                                                                      //functie pentru a modifica datele despre pilot
    system("cls");
    FILE *f;
    int flag=0;
    struct driver p,s;
    char name [50];
    f=fopen("data.txt","rb+");
    if(f==NULL){
        printf("Error opening file");
        exit(1);
    }else{
        system("cls");
        printf("\n\tEnter pilot name to edit:\n");
        fgets(name,50,stdin);
        strtok(name, "\n");
        while(fread(&p,sizeof(p),1,f)==1){
            if (strcmp(name,p.name)==0){
                printf("\nPILOT FOUNDE!\n\tEnter Name:\n");
                fgets(s.name,50,stdin);
                strtok(s.name, "\n");
                printf("\n\tEnter Number:\n");
                fgets(s.number,5,stdin);
                strtok(s.number, "\n");
                printf("\n\tEnter Team:\n");
                fgets(s.team,50,stdin);
                strtok(s.team, "\n");
                printf("\n\tEnter Number of Wins:\n");
                fgets(s.gpwin, 5, stdin);
                strtok(s.gpwin, "\n");
                printf("\n\tEnter best time:\n");
                fgets(s.time, 15, stdin);
                strtok(s.time, "\n");
                fseek(f,-sizeof(p),SEEK_CUR);
                fwrite(&s,sizeof(p),1,f);
                flag=1;
                break;
            }
            fflush(stdin);
        }
        if (flag==1)
            printf("\n\tRecord modified");
        else
            printf("Record Not Found");

        fclose(f);
    }
    printf("\nEnter any key to go back");
    getch();
    system("cls");
    menu();
}

void deleteRecord(){                                                                                                    //functie pentru a sterge un pilot folosind un alt fisier temporar pe care
    system("cls");                                                                                             //il redenumim inapoi in fisierul de baza dupa ce stergem pilotul
    struct driver p;
    FILE *f, *ft;
    int flag;
    char name[50];
    f=fopen("data.txt", "rb");
    if (f==NULL){
        printf("File error");
    }else{
        ft=fopen("temp.txt","wb+");
        if (ft==NULL){
            printf("File opening error");
        }else{
            printf("\n\tEnter pilot name:");
            fgets(name,50, stdin);
            strtok(name, "\n");
            fflush(stdin);
            while(fread(&p,sizeof(p),1,f)==1){
                if(strcmp(p.name,name)!=0)
                    fwrite(&p,sizeof(p),1,ft);
                if(strcmp(p.name,name)==0)
                    flag=1;
            }
            fclose(f);
            fclose(ft);
            if (flag!=1){
                printf("\n\tNo pilot record to delete!");
                remove ("temp.txt");
            }else{
                remove("data.txt");
                rename("temp.txt","data.txt");
                printf("\n\tPilot Deleted successfully!");
            }
        }
    }
    printf("\nEnter any key to go back");
    getch();
    system("cls");
    menu();
}


int main(void) {                                                                                                        //setez culoarea programului si apelez functia meniu
    system("color 4f");
    menu();
    return 0;
}
