#include <stdio.h>
#include <string.h>
#include <conio.h>
#include<stdlib.h>
struct client
    {
    char name[100];
    char email[100];
    char password[50];
    char account_No[50];
    int balance;
    };

int isExist(char *accountNo,int display);
void copyFile(char *write,char *read);
void Sign_In()
    {

    FILE *f;
    char file[]="registerRecord.txt";
    f = fopen(file,"a");
    struct client c;
    printf("\tName:");
    fflush(stdin);
    gets(c.name);
    printf("\tEmail:");
    gets(c.email);
    printf("\tPassword:");
    fflush(stdin);
    gets(c.password);
    printf("\tAccount No:");
    gets(c.account_No);
    printf("\tInitial Balance:");
    scanf("%d",&c.balance);
    if(isExist(c.account_No,0)==0)
        {
            fprintf(f,"%s,",c.account_No);
            fprintf(f,"%s,",c.name);
            fprintf(f,"%s,",c.email);
            fprintf(f,"%s,",c.password);
            fprintf(f,"%d\n",c.balance);
            printf("\t Registration completed\n");
        }
    else
        printf("\tAccount Number Already Exists.\n");
    fclose(f);
    int garbage;
    printf("Press any key to return to main menu.");
    scanf("%d",&garbage);
    getchar();
    }

int Login_In()
    {
    int flag=0;
    char accountNo[50];
    char password[50];
    printf("\tEnter Account No:");
    gets(accountNo);
    printf("\tEnter Password:");
    gets(password);
    FILE *f,*f1;
    char file[]="registerRecord.txt";
    f = fopen(file,"r");
    char fileName[]="tempActive.txt";
    f1 = fopen(fileName,"w");
    int lineLength=999;
    char line[lineLength];
    while(fgets(line, lineLength, f))
        {
        char word[5][100]= {{}};
        int row=0;
        int column=0;
        for(int i=0; line[i]!='\0'; i++)
            {
            if(line[i]==',')
                {
                row++;
                column=0;
                }
            else
                {
                word[row][column++]=line[i];
                }
            }
        if(flag==0 && strcmp(word[0],accountNo)==0 && strcmp(word[3],password)==0)
            {
                fputs(word[0],f1);
                fputc(' ',f1);
                fputs(word[1],f1);
                fputc(' ',f1);
                fputs(word[2],f1);
                fputc(' ',f1);
                fputs(word[3],f1);
                fputc(' ',f1);
                fputs(word[4],f1);
                fputc(' ',f1);
                flag=1;
                break;
            }
        }
    fclose(f);
    fclose(f1);
    if(flag==1)
        printf("\t\t\t\t\t Logged in Successfully.\n");
    else
        printf("\t\t\t\t\t Wrong Password.\n");
    printf("Press any key to return to main menu.");
    int garbage;
    scanf("%d",&garbage);
    getchar();
    return flag;
    }
int isExist(char *accountNo,int display)
    {
    FILE *f;
    char file[]="registerRecord.txt";
    f = fopen(file,"r");
    int lineLength=999;
    char line[lineLength];
    while(fgets(line, lineLength, f))
        {
        char word[5][50]= {};
        int row=0;
        int column=0;
        for(int i=0; line[i]!='\0'; i++)
            {
            if(line[i]==',')
                {
                row++;
                column=0;
                }
            else
                {
                word[row][column++]=line[i];
                }
            }
        if(strcmp(word[0],accountNo)==0)
            {
            if(display==1)
                {
                printf("Enter password:");
                char password[50];
                fflush(stdin);
                gets(password);
                if(strcmp(password,word[3])==0){
                        printf("\tAccount No:%s\n",word[0]);
                        printf("\tName:%s\n",word[1]);
                        printf("\tEmail:%s\n",word[2]);
                        printf("\tBalance:%s\n",word[4]);
                        printf("Press any key to return to main menu.");
                        int garbage;
                        scanf("%d",&garbage);
                    }
                else
                    printf("Password do not match.");
                return 0;
                }
            return 1;
            }
        }
    fclose(f);
    return 0;
    }
int Transaction(char *accountNo,int debit)
    {
    struct client c;
    int flag=0;
    char password[50];
    int lineLength=999;
    char line[lineLength];
    char file[]="registerRecord.txt";
    char file1[]="temp.txt";
    FILE *f,*f1;
    f = fopen(file,"r");
    f1 = fopen(file1,"w");
    while(fgets(line, lineLength, f))
        {
        char word[5][100]= {};
        int row=0,column=0;
        for(int i=0; line[i]!='\0'; i++)
            {
            if(line[i]==',')
                {
                row++;
                column=0;
                }
            else
                {
                word[row][column++]=line[i];
                }
            }
        if(strcmp(word[0],accountNo)==0 && flag==0)
            {
            strcpy(c.account_No,word[0]);
            strcpy(c.name,word[1]);
            strcpy(c.email,word[2]);
            strcpy(c.password,word[3]);
            c.balance = atoi(word[4]);
            printf("\tEnter password");
            fflush(stdin);
            gets(password);
            if(strcmp(password,c.password)==0)
                {
                printf("\tPassword matched.\n");
                int amount;
                if(debit==1){
                    printf("\n\tWithDraw money :");
                    scanf("%d",&amount);
                    c.balance-=amount;
                }
                else{
                    printf("\n\tDeposit money :");
                    scanf("%d",&amount);
                    c.balance+=amount;
                }
                fprintf(f1,"%s,",c.account_No);
                fprintf(f1,"%s,",c.name);
                fprintf(f1,"%s,",c.email);
                fprintf(f1,"%s,",c.password);
                fprintf(f1,"%d\n",c.balance);
                printf("%d",c.balance);
                flag=1;
                continue;
                }
            else
                printf("\tPassword not matching");
            }
        fprintf(f1,"%s",line);
        }
    fclose(f);
    fclose(f1);
    if(flag==1)
        copyFile(file,file1);
    return flag;
    }
void copyFile(char *write,char *read)
    {
    FILE *f1,*f2;
    f1 = fopen(read,"r");
    f2 = fopen(write,"w");
    int lineLength=9999;
    char line[lineLength];
    while(fgets(line, lineLength, f1))
        {
        fputs(line,f2);
        }
    fclose(f1);
    fclose(f2);
    }
void displayClientVariable(struct client c){
        printf("\tName:%s\n",c.name);
        printf("\tEmail:%s\n",c.email);
        printf("\tAccount No:%s\n",c.account_No);
        printf("\tPassword:%s\n",c.password);
        printf("\tBalance:%d\n",c.balance);
        printf("Press any key to return to main menu.");
        int garbage;
        scanf("%d",&garbage);
    }
int update_Info(char *accountNo)
    {
    struct client c;
    int flag=0;
    int lineLength=9999;
    char line[lineLength];
    char file[]="registerRecord.txt";
    char file1[]="temp.txt";
    FILE *f,*f1;
    f = fopen(file,"r");
    f1 = fopen(file1,"w");
    while(fgets(line, lineLength, f))
        {
        int row=0,column=0;
        char word[5][100]= {};
        for(int i=0; line[i]!='\0'; i++)
            {
            if(line[i]==',')
                {
                row++;
                column=0;
                }
            else
                {
                word[row][column++]=line[i];
                }
            }
        if(strcmp(word[0],accountNo)==0 && flag==0)
            {
            strcpy(c.account_No,word[0]);
            strcpy(c.name,word[1]);
            strcpy(c.email,word[2]);
            strcpy(c.password,word[3]);
            sscanf(word[4], "%d", &c.balance);
            printf("Verify your  password:");
            char password[50];
            fflush(stdin);
            gets(password);
            if(strcmp(password,c.password)==0)
                {
                printf("\n\tYou account number[Its unique u can't change it] :");
                puts(c.account_No);
                printf("\n\tPassword matched.\n");
                printf("\n\tName :");
                fflush(stdin);
                gets(c.name);
                printf("\n\tEmail :");
                gets(c.email);
                printf("\n\tPassword :");
                gets(c.password);
                fprintf(f1,"%s,",c.account_No);
                fprintf(f1,"%s,",c.name);
                fprintf(f1,"%s,",c.email);
                fprintf(f1,"%s,",c.password);
                fprintf(f1,"%d\n",c.balance);
                flag=1;
                continue;
                }
            else
                {
                printf("\tPassword NOT matching");
                return 0;
                }
            }
        fprintf(f1,"%s",line);
        }
    fclose(f);
    fclose(f1);
    if(flag==1)
        copyFile(file,file1);
    return flag;

    }

int DeleteAccount(char *accountNo){
    struct client c;
    int flag=0;
    int lineLength=9999;
    char line[lineLength];
    char file[]="registerRecord.txt";
    char file1[]="temp.txt";
    FILE *f,*f1;
    f = fopen(file,"r");
    f1 = fopen(file1,"w");
    while(fgets(line, lineLength, f))
        {
        int row=0,column=0;
        char word[5][100]= {};
        for(int i=0; line[i]!='\0'; i++)
            {
            if(line[i]==',')
                {
                row++;
                column=0;
                }
            else
                {
                word[row][column++]=line[i];
                }
            }
        if(strcmp(word[0],accountNo)==0 && flag==0)
            {
            strcpy(c.account_No,word[0]);
            strcpy(c.name,word[1]);
            strcpy(c.email,word[2]);
            strcpy(c.password,word[3]);
            sscanf(word[4], "%d", &c.balance);
            printf("Verify your  password:");
            char password[50];
            fflush(stdin);
            gets(password);
            if(strcmp(password,c.password)==0)
                {
                flag=1;
                printf("\n\tPassword matched.\n");
                continue;
                }
            else
                {
                printf("\tPassword does not  match.\n");
                return 0;
                }
            }
        fprintf(f1,"%s",line);
        }
    fclose(f);
    fclose(f1);
    if(flag==1)
        copyFile(file,file1);
    return flag;
}
void menu()
    {
        system("cls");
        printf("\t\t\t\t\tBank Management System\n\n");
        printf("\n\n\t\t\t\t\tMAIN\tMENU\n\n");
        printf("\n\tPress 1: transaction.");
        printf("\n\tPress 2: Update information of Existing members.");
        printf("\n\tPress 3: Search information of another account [If you own]");
        printf("\n\tPress 4: Delete Existing members.");
        printf("\n\tPress 5: Display information of Existing members.");
        printf("\n\tPress 6: Exit.");
        printf("\n\tEnter a option you wanted to go for:\n");
    }

int main(){
    int n,flag=0;
    here:
    while(1==1){
        system("cls");
        printf("\t\t\t\t\tBank Management System\n\n");
        printf("\t Press 1. Login\n");
        printf("\t Press 2. Register\n");
        printf("\t Press 3. Exit\n");
        printf("\t");
        scanf("%d",&n);
        getchar();
        if(n==1)
            flag=Login_In();
        else if(n==2)
            Sign_In();
        else if(n==3)
            return 0;
        if(flag==1)
            break;
        else
            continue;
        getchar();
        printf("\tPress any key to go back to menu.\n");
        int garbage;
        scanf("%d",&garbage);
    }
        char file[]="tempActive.txt";
        FILE *f;
        f = fopen(file,"r");
        struct client c;
        fscanf(f,"%s %s %s %s %d", c.account_No,c.name,c.email,c.password,&c.balance);
        printf("\n%s",c.account_No);
        printf("\n%s",c.name);
        printf("\n%s",c.email);
        printf("\n%s",c.password);
        printf("\n%d",c.balance);
        fclose(f);
        while(flag==1){
            menu();
            fflush(stdin);
            scanf("%d",&n);
            getchar();
             if(n==1){
                int debit;
                printf("\n\tPress 1 to withdraw money.");
                printf("\n\tPress 2 to Deposit money.");
                scanf("%d",&debit);
                getchar();
                Transaction(c.account_No,debit);
            }
            else if(n==2){
                update_Info(c.account_No);
            }
            else if(n==3){
                printf("To search and account,Enter Account Number:");
                char srID[50];
                fflush(stdin);
                gets(srID);
                isExist(srID,1);
            }
            else if(n==4){
                if(DeleteAccount(c.account_No)==1){
                    goto here;
                }
            }
            else if(n==5){
                isExist(c.account_No,1);
            }
            else if(n==6){
                return 0;
            }
        }
    return 0;
}
