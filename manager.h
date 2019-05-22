#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define  FAULSE         0
#define  STUDENT        4
#define  SYSTEM         3
#define  TEACHER        2
#define  MANAGER        1
#define  INIT           0
#define  ENTER          13
#define  BACKSPACE      8
#define  ALL            100
#define  LENDABLE       1
#define  LENTH          30
#define  SIGN_IN        1
#define  MAIN           2
#define  DEL_BOOK       3
#define  DEL_USER       4
#define  INIT_PWD       5
#define  SECURE         128
#define  NAME_LENTH     16
#define  PWD_LENTH      16
#define  AUTHOR_LEN     16

struct books{
      int       lendable;           //״̬
      char      name[NAME_LENTH];   //��Ŀ
      char      author[AUTHOR_LEN]; //����
      double    price;              //�۸�
      struct    books *next;        //���ָ��
};                                  //ͼ����Ϣ

struct member {
       char name[NAME_LENTH];       //�û���
       char password[PWD_LENTH];    //����
       int  user_type;              //�û�����
}user[100];                         //�û���Ϣ

typedef struct books book;
typedef book * point;

point temp,Head,Tail;

FILE * Pwd;
FILE * Userreord;
FILE * Book;

int  book_amount=0;         //ͼ������
int  user_amount=0;         //�û�����
int  current_user;          //��ǰ�û�
int  l = 0;
char username[NAME_LENTH];  //�û���
char gpassword[PWD_LENTH];  //���������

void init_all();            //��ʼ������
int  login();               //��½ģ��
void title(int);            //��ӡ����
void print_menu(int);       //��ӡ�˵�
void add_book();            //���ͼ��
void del_book();            //ɾ��ͼ��
void add_user();            //����û�
void del_user();            //ɾ���û�
void list_book(int);        //�г�ͼ����Ϣ
void list_user();           //�г��û���Ϣ
char *get_password();       //��ȡ����
int  change_password();     //��������
void init_password();       //��ʼ���û�����
void update_user();         //����ͼ������
void update_book();         //�����û�����
void back_up();             //��������

char *get_password()        //��ȡ����
{
    int t=0;
    while (1)
    {
        gpassword[t]=_getch();
        if      (gpassword[t] == BACKSPACE && t==0 ) ;
        else if (t > 15 && gpassword[t] != ENTER );
        else if (gpassword[t] == BACKSPACE)
        {
            printf("\b \b");
            t--;
        }
        else if (gpassword[t] == ENTER)
            break;
        else
        {
            t++;
            printf("*");
        }
    }
    for (int i = t ; i < PWD_LENTH ; i++)
        gpassword[i]='\0';
    return gpassword;
}

void init_all()             //��ʼ������
{
    char tmp[30];
    user_amount=0;
    book_amount=0;
    Book=fopen("books.txt","r");
    temp = (point)malloc(sizeof(book));
    Head=Tail=temp;
    while(fgets(temp->name,LENTH,Book) != NULL && temp->name[0] != '\n')  //��ȡͼ����Ϣ
    {
        fgets(temp->author,LENTH,Book);
        temp->name[strlen(temp->name)-1]='\0';
        temp->author[strlen(temp->author)-1]='\0';
        fscanf(Book,"%lf",&temp->price);
        fgets(tmp,LENTH,Book);
        fscanf(Book,"%d",&temp->lendable);
        fgets(tmp,LENTH,Book);
        Tail->next=temp;
        Tail=temp;
        temp = (point)malloc(sizeof(book));
        book_amount++;
    }
    fclose(Book);
    Pwd=fopen("pwd.bd","rb");
    int t=0,i=0;
    while (!feof(Pwd))                                   //��ȡ�û���Ϣ
    {
        fread(user[t].name,sizeof(user[t].name),1,Pwd);
        fread(user[t].password,sizeof(user[t].password),1,Pwd);
        fread(&user[t].user_type,sizeof(int),1,Pwd);
        for (i = 0 ; i < NAME_LENTH ; i ++ )
        {
            user[t].name[i] -= SECURE;
            user[t].password[i] -= SECURE;
        }
        user[t++].user_type -= SECURE;
        user_amount++;
    }
    fclose(Pwd);
}

int  login()                //�û���¼ģ��
{
    int i;
    char * password;
    title(SIGN_IN);
    printf("�û���:");
    scanf("%s",&username);
    l=0;
    while(1)
    {
        for (i = 0 ; i < NAME_LENTH ; i ++ )      //��ȡ�û��� ���ಿ����Ϊ0
            if (username[i] == '\0')
            {
                 for (int j = i+1 ; j < NAME_LENTH ; j ++ )
                    username[j] = '\0';
                break;
            }
        printf("����:");
        password=get_password();
        for (i = 0 ; i <  user_amount; i++)
        {
            if ((strcmp(user[i].name,username))==0)
            {
                if ((strcmp(user[i].password,password))==0)
                {
                   current_user=i;
                   return user[current_user].user_type;
                }
                break;
            }
        }
        if ((strcmp(user[i].name,username))== 0)
            printf("\n�������\n���س����������� (��0�˳�)");
        else
            printf("\n�û��������ڣ�\n���س����������� ��0�˳�");
        if (_getch() == 48)
            return FALSE;
        if ((strcmp(user[i].name,username))==0)
        {
            title(SIGN_IN);
            printf("�û���:%s\n",username);
        }
        else
        {
           title(SIGN_IN);
           printf("�û���:");
           scanf("%s",&username);
        }
    }
}

void print_menu(int user)   //��ӡ�˵�
{
    switch (user)
    {
        case INIT:
            title(MAIN);
            printf("        =======================================\n");
            printf("        *       1 ��¼ϵͳ                    *\n");
            printf("        *                                     *\n");
            printf("        *       0 �˳�ϵͳ                    *\n");
            printf("        =======================================\n");
            break;
        case SYSTEM:
            title(MAIN);
            printf("          С��ͼ�����ϵͳ��������ϵͳ����Ա     \n");
            printf("        =======================================\n");
            printf("        *       1 ��ʾ�û�                    *\n");
            printf("        *       2 ����û�                    *\n");
            printf("        *       3 ɾ���û�                    *\n");
            printf("        *       4 ��ʾͼ��                    *\n");
            printf("        *       5 ɾ��ͼ��                    *\n");
            printf("        *       6 �������ͼ��                *\n");
            printf("        *       7 ��ʼ���û�����              *\n");
            printf("        *       8 �޸ĵ�¼����                *\n");
            printf("        *       9 ϵͳ����                    *\n");
            printf("        *       0 ע��                        *\n");
            printf("        =======================================\n");
            break;
        case MANAGER:
            title(MAIN);
            printf("           С��ͼ�����ϵͳ��������ͼ�����Ա   \n");
            printf("        =======================================\n");
            printf("        *       1 ͼ���ѯ                    *\n");
            printf("        *       2 �û�������Ϣ��ѯ            *\n");
            printf("        *       3 ����                        *\n");
            printf("        *       4 ����                        *\n");
            printf("        *       5 ������������                *\n");
            printf("        *       6 �������ͼ��                *\n");
            printf("        *       7 �޸ĵ�¼����                *\n");
            printf("        *       0 ע��                        *\n");
            printf("        =======================================\n");
            break;
        case STUDENT:
            title(MAIN);
            printf("            С��ͼ�����ϵͳ��������ѧ���û�     \n");
            printf("        =======================================\n");
            printf("        *       1 ͼ���ѯ                    *\n");
            printf("        *       2 ��ѯ��ǰ�ѽ���Ŀ            *\n");
            printf("        *       3 ����                        *\n");
            printf("        *       4 �޸ĸ�����Ϣ                *\n");
            printf("        *       5 �޸ĵ�¼����                *\n");
            printf("        *       0 ע��                        *\n");
            printf("        =======================================\n");
            break;
        case TEACHER:
            title(MAIN);
            printf("            С��ͼ�����ϵͳ����������ʦ�û�     \n");
            printf("        =======================================\n");
            printf("        *       1 ͼ���ѯ                    *\n");
            printf("        *       2 ��ѯ��ǰ�ѽ���Ŀ            *\n");
            printf("        *       3 ����                        *\n");
            printf("        *       4 ��ѯѧ���������            *\n");
            printf("        *       5 �޸ĸ�����Ϣ                *\n");
            printf("        *       6 �޸ĵ�¼����                *\n");
            printf("        *       0 ע��                        *\n");
            printf("        =======================================\n");
            break;
        }
}

void list_book(int mode)    //��ӡͼ����Ϣ
{
        title(MAIN);
        printf("======================================================================\n");
        printf("     ����                     ����                �۸�        ͼ��״̬\n");
        int t=1;
        switch (mode)
        {
            case ALL:
                for(temp=Head; temp != NULL ; temp=temp->next)
                 {
                    printf("\n%3d��%-25s%-20s%-10.2lf  ",t++,temp->name,temp->author,temp->price);
                    if (temp->lendable == TRUE)
                        printf("�ɽ�");
                    else
                        printf("���ɽ�");
                 }  break;
            case LENDABLE:
                for(temp=Head; temp != NULL ; temp=temp->next)
                   if (temp->lendable == TRUE )
                   {
                          printf("\n%3d��%-25s%-20s%-10.2lf  ",t++,temp->name,temp->author,temp->price);
                          printf("�ɽ�");
                   }  break;
        }
    getchar();
}

void add_user()             //����û�
{
    int t;
    char *password,*tmp;
    title(MAIN);
    printf("        =======================================\n");
    printf("        *       1 ����û�                    *\n");
    printf("        *                                     *\n");
    printf("        *       0 �˳�                        *\n");
    printf("        =======================================\n");
    while(_getch()  != '0' )
    {
        printf("�������û���:");
        gets(user[user_amount].name);
        while (1)
        {
            t=0;
            printf("��������  ��:");
            password=get_password();
            if (password[t] == ENTER && t ==0 )
                return;
            password[t]='\0';
            printf("\n��ȷ����  ��:");
            tmp=get_password();
            if (strcmp(tmp,password)==0)
            {
                strcpy(user[user_amount].password,tmp);
                printf("\n�������û������\n1��ϵͳ����Ա 2��ͼ�����Ա 3����ʦ 4��ѧ��:\n");
                scanf("%d",&user[user_amount].user_type);
                getchar();                               //�����û������ļ�
                user_amount++;
                update_user();
                title(MAIN);
                printf("�û���ӳɹ�\n");
                printf("        =======================================\n");
                printf("        *       1 �������                    *\n");
                printf("        *                                     *\n");
                printf("        *       0 �˳�                        *\n");
                printf("        =======================================\n");
                break;
            }
            else
            {
                title(MAIN);
                printf("�������벻һ������������ �س����˳�\n");
                printf("        =======================================\n");
                printf("        *       1 ����û�                    *\n");
                printf("        *                                     *\n");
                printf("        *       0 �˳�                        *\n");
                printf("        =======================================\n");
                printf("�������û���:%s\n",user[user_amount].name);
            }
         }
    }
}

void add_book()             //���ͼ��
{
    int tmp;
    title(MAIN);
    printf("        =======================================\n");
    printf("        *       1 ���ͼ��                    *\n");
    printf("        *                                     *\n");
    printf("        *       0 �˳�                        *\n");
    printf("        =======================================\n");
    Book=fopen("books.txt","a");
    while(_getch()  != '0' )
    {
        temp = (point)malloc(sizeof(book));
        printf("����������:");
        gets(temp->name);
        printf("����������:");
        gets(temp->author);
        printf("������۸�:");
        scanf("%lf",&temp->price);
        temp->lendable=TRUE;             //����ͼ�������ļ�
        fprintf(Book,"%s\n%s\n%.2lf\n%d\n",temp->name,temp->author,temp->price,temp->lendable);
        title(MAIN);
        printf("ͼ����ӳɹ�\n");
        printf("        =======================================\n");
        printf("        *       1 �������                    *\n");
        printf("        *                                     *\n");
        printf("        *       0 �˳�                        *\n");
        printf("        =======================================\n");
        Tail->next=temp;
        Tail=temp;
    }
    fclose(Book);
}

void del_book()             //ɾ��ͼ��
{
    char tmp[NAME_LENTH];
    point str,pre;
    title(DEL_BOOK);
    printf("��������Ҫɾ����ͼ��:");
    while(1)
    {
        int i = 1;
        char t;
        gets(tmp);
        for(str=temp=Head; temp != NULL ; i++)
        {
            if (strcmp(tmp,temp->name) == 0)
            {
                pre=temp;
                str->next=temp->next;
                book_amount--;
                free(temp);
                Book=fopen("books.txt","w");        //����ͼ�������ļ�
                for(temp=Head; temp != NULL ;temp=temp->next )
                    fprintf(Book,"%s\n%s\n%.2lf\n%d\n",temp->name,temp->author,temp->price,temp->lendable);
                fclose(Book);
                str=temp=pre;
                break;
            }
            str=temp;
            temp=temp->next;

        }
        if (i == book_amount )
        {
            title(DEL_BOOK);
            printf("��ͼ�鲻���� ����������:");
        }
        else
        {
            title(DEL_BOOK);
            printf("ͼ��ɾ���ɹ� �س����˳� ����ɾ������������:\n");
        }
        t =_getch();
        if (t == ENTER)
        {
                getchar();
                break;
        }
  }
  init_all();
}

void title(tmp)             //��ӡ����ͷ
{
    system("CLS");
    printf("��ӭʹ�ý���ʦ��ͼ�����ϵͳ!\n\n");
    switch (tmp)
    {
        case DEL_USER:
            printf("С��ͼ�����ϵͳ---->ɾ���û�\n");
            break;
        case INIT_PWD:
            printf("С��ͼ�����ϵͳ---->��������\n");
            break;
        case SIGN_IN:
            printf("С��ͼ�����ϵͳ---->�û���¼\n");
            break;
        case DEL_BOOK:
            printf("С��ͼ�����ϵͳ---->ɾ��ͼ��\n");
            break;
    }
    if (tmp != MAIN)
        printf("=============================\n");
}

void list_user()            //�г������û�
{
        title(MAIN);
        printf("=============================\n\n");
        for (int i = 0 ; i < user_amount ; i ++)
             printf("%d��  %s \n",i+1,user[i].name);
        getchar();
}

void del_user()             //ɾ���û�
{
    char tmp[NAME_LENTH];
    int i;
    title(DEL_USER);
    printf("��������Ҫɾ�����û�:");
    while (1)
    {
        scanf("%s",&tmp);   getchar();
        if (strlen(tmp) == 1 && tmp[0] == '0' )
            break;
        for ( i = 0 ; i < user_amount && strcmp(tmp,user[i].name) != 0 ; i ++ )
            ;
        if (i < user_amount)
        {
            update_user();
            init_all();
            title(DEL_USER);
            printf("�û�ɾ���ɹ���\n����ɾ���������û���(����0�˳�):");
        }
        else
        {
            title(DEL_USER);
            printf("�û���δ�ҵ���\n����������(����0�˳�):");
        }
    }
}

void init_password()        //��ʼ���ǹ���Ա�û�����
{
    for (int t = 0 ; t < user_amount ; t ++ )       //�����û�����
        if (user[t].user_type != SYSTEM)
            for (int i = '1' ; i < '9' ; i ++ )
                user[t].password[i-48] = i;
    update_user();           //�����û������ļ�
    init_all();
}

int change_password()       //���ĵ�ǰ�û�����
{
    char *tmp,*pass;
    title(INIT_PWD);
    printf("�����뵱ǰ�û�����:");
    pass = get_password();                  //��ȡ��ǰ����
    while(1)
    {
        if ((strcmp(user[current_user].password,pass))==0)
        {
            printf("\n������������:");
            pass=get_password();            //��ȡ������
            printf("\n��ȷ����  ��:");
            tmp=get_password();             //ȷ��������
            if (strcmp(tmp,pass)==0)
            {
                strcpy(user[current_user].password,tmp);    //�����û�����
                update_user();                              //���������ļ�
                printf("\n��������ɹ�,�����µ�¼��");
                _getch();
                getchar();
                return TRUE;
            }
            else
            {
                printf("\n��������ʧ��(�������벻һ��),����������:");
                title(INIT_PWD);
            }
        }
        else
        {
            title(INIT_PWD);
            printf("\n��������ʧ��(�������),����������(����0�˳�):");
            pass=get_password();
            if(pass[0] == '0' && pass[1] == '\0')
                return FAULSE;
        }
    }
}

void back_up()              //���������ļ�
{
    int t;
    FILE * user_text;
    FILE * book_text;
    user_text=fopen("pwd_.bk","wb");         //����ͼ����Ϣ
    for ( t = 0 ; t < user_amount ; t ++ )
        fprintf(user_text,"%s\n%s\n%d\n",user[t].name,user[t].password,user[t].user_type);
    fclose(user_text);

    book_text=fopen("book_.bk","wb");        //�����û���Ϣ
    for(temp=Head; temp != NULL; temp=temp->next)
        fprintf(book_text,"%s\n%s\n%.2lf\n%d\n",temp->name,temp->author,temp->price,temp->lendable);
    fclose(book_text);
}

void update_book()          //����ͼ�������ļ�
{

}

void update_user()          //�����û������ļ�
{
    FILE *user_text=fopen("pwd.bd","rb");
    int t=0,i=0;
    while (!feof(user_text))                                   //��ȡ�û���Ϣ
    {
        fread(user[t].name,sizeof(user[t].name),1,user_text);
        fread(user[t].password,sizeof(user[t].password),1,user_text);
        fread(&user[t].user_type,sizeof(int),1,user_text);
        for (i = 0 ; i < NAME_LENTH ; i ++ )
        {
            user[t].name[i] -= SECURE;
            user[t].password[i] -= SECURE;
        }
        user[t].user_type -= SECURE;
        t++;
    }
    fclose(user_text);
}

