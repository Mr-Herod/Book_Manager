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
      int       lendable;           //状态
      char      name[NAME_LENTH];   //书目
      char      author[AUTHOR_LEN]; //作者
      double    price;              //价格
      struct    books *next;        //结点指针
};                                  //图书信息

struct member {
       char name[NAME_LENTH];       //用户名
       char password[PWD_LENTH];    //密码
       int  user_type;              //用户类型
}user[100];                         //用户信息

typedef struct books book;
typedef book * point;

point temp,Head,Tail;

FILE * Pwd;
FILE * Userreord;
FILE * Book;

int  book_amount=0;         //图书数量
int  user_amount=0;         //用户数量
int  current_user;          //当前用户
int  l = 0;
char username[NAME_LENTH];  //用户名
char gpassword[PWD_LENTH];  //输入的密码

void init_all();            //初始化数据
int  login();               //登陆模块
void title(int);            //打印标题
void print_menu(int);       //打印菜单
void add_book();            //添加图书
void del_book();            //删除图书
void add_user();            //添加用户
void del_user();            //删除用户
void list_book(int);        //列出图书信息
void list_user();           //列出用户信息
char *get_password();       //读取密码
int  change_password();     //更换密码
void init_password();       //初始化用户密码
void update_user();         //更新图书数据
void update_book();         //更新用户数据
void back_up();             //备份数据

char *get_password()        //获取密码
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

void init_all()             //初始化数据
{
    char tmp[30];
    user_amount=0;
    book_amount=0;
    Book=fopen("books.txt","r");
    temp = (point)malloc(sizeof(book));
    Head=Tail=temp;
    while(fgets(temp->name,LENTH,Book) != NULL && temp->name[0] != '\n')  //读取图书信息
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
    while (!feof(Pwd))                                   //读取用户信息
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

int  login()                //用户登录模块
{
    int i;
    char * password;
    title(SIGN_IN);
    printf("用户名:");
    scanf("%s",&username);
    l=0;
    while(1)
    {
        for (i = 0 ; i < NAME_LENTH ; i ++ )      //获取用户名 多余部分置为0
            if (username[i] == '\0')
            {
                 for (int j = i+1 ; j < NAME_LENTH ; j ++ )
                    username[j] = '\0';
                break;
            }
        printf("密码:");
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
            printf("\n密码错误！\n按回车键重新输入 (按0退出)");
        else
            printf("\n用户名不存在！\n按回车键重新输入 按0退出");
        if (_getch() == 48)
            return FALSE;
        if ((strcmp(user[i].name,username))==0)
        {
            title(SIGN_IN);
            printf("用户名:%s\n",username);
        }
        else
        {
           title(SIGN_IN);
           printf("用户名:");
           scanf("%s",&username);
        }
    }
}

void print_menu(int user)   //打印菜单
{
    switch (user)
    {
        case INIT:
            title(MAIN);
            printf("        =======================================\n");
            printf("        *       1 登录系统                    *\n");
            printf("        *                                     *\n");
            printf("        *       0 退出系统                    *\n");
            printf("        =======================================\n");
            break;
        case SYSTEM:
            title(MAIN);
            printf("          小型图书管理系统————系统管理员     \n");
            printf("        =======================================\n");
            printf("        *       1 显示用户                    *\n");
            printf("        *       2 添加用户                    *\n");
            printf("        *       3 删除用户                    *\n");
            printf("        *       4 显示图书                    *\n");
            printf("        *       5 删除图书                    *\n");
            printf("        *       6 批量添加图书                *\n");
            printf("        *       7 初始化用户密码              *\n");
            printf("        *       8 修改登录密码                *\n");
            printf("        *       9 系统备份                    *\n");
            printf("        *       0 注销                        *\n");
            printf("        =======================================\n");
            break;
        case MANAGER:
            title(MAIN);
            printf("           小型图书管理系统————图书管理员   \n");
            printf("        =======================================\n");
            printf("        *       1 图书查询                    *\n");
            printf("        *       2 用户借书信息查询            *\n");
            printf("        *       3 借书                        *\n");
            printf("        *       4 还书                        *\n");
            printf("        *       5 按借书量排序                *\n");
            printf("        *       6 批量添加图书                *\n");
            printf("        *       7 修改登录密码                *\n");
            printf("        *       0 注销                        *\n");
            printf("        =======================================\n");
            break;
        case STUDENT:
            title(MAIN);
            printf("            小型图书管理系统————学生用户     \n");
            printf("        =======================================\n");
            printf("        *       1 图书查询                    *\n");
            printf("        *       2 查询当前已借书目            *\n");
            printf("        *       3 续借                        *\n");
            printf("        *       4 修改个人信息                *\n");
            printf("        *       5 修改登录密码                *\n");
            printf("        *       0 注销                        *\n");
            printf("        =======================================\n");
            break;
        case TEACHER:
            title(MAIN);
            printf("            小型图书管理系统————教师用户     \n");
            printf("        =======================================\n");
            printf("        *       1 图书查询                    *\n");
            printf("        *       2 查询当前已借书目            *\n");
            printf("        *       3 续借                        *\n");
            printf("        *       4 查询学生借书情况            *\n");
            printf("        *       5 修改个人信息                *\n");
            printf("        *       6 修改登录密码                *\n");
            printf("        *       0 注销                        *\n");
            printf("        =======================================\n");
            break;
        }
}

void list_book(int mode)    //打印图书信息
{
        title(MAIN);
        printf("======================================================================\n");
        printf("     书名                     作者                价格        图书状态\n");
        int t=1;
        switch (mode)
        {
            case ALL:
                for(temp=Head; temp != NULL ; temp=temp->next)
                 {
                    printf("\n%3d、%-25s%-20s%-10.2lf  ",t++,temp->name,temp->author,temp->price);
                    if (temp->lendable == TRUE)
                        printf("可借");
                    else
                        printf("不可借");
                 }  break;
            case LENDABLE:
                for(temp=Head; temp != NULL ; temp=temp->next)
                   if (temp->lendable == TRUE )
                   {
                          printf("\n%3d、%-25s%-20s%-10.2lf  ",t++,temp->name,temp->author,temp->price);
                          printf("可借");
                   }  break;
        }
    getchar();
}

void add_user()             //添加用户
{
    int t;
    char *password,*tmp;
    title(MAIN);
    printf("        =======================================\n");
    printf("        *       1 添加用户                    *\n");
    printf("        *                                     *\n");
    printf("        *       0 退出                        *\n");
    printf("        =======================================\n");
    while(_getch()  != '0' )
    {
        printf("请输入用户名:");
        gets(user[user_amount].name);
        while (1)
        {
            t=0;
            printf("请输入密  码:");
            password=get_password();
            if (password[t] == ENTER && t ==0 )
                return;
            password[t]='\0';
            printf("\n请确认密  码:");
            tmp=get_password();
            if (strcmp(tmp,password)==0)
            {
                strcpy(user[user_amount].password,tmp);
                printf("\n请输入用户名类别\n1、系统管理员 2、图书管理员 3、老师 4、学生:\n");
                scanf("%d",&user[user_amount].user_type);
                getchar();                               //更新用户数据文件
                user_amount++;
                update_user();
                title(MAIN);
                printf("用户添加成功\n");
                printf("        =======================================\n");
                printf("        *       1 继续添加                    *\n");
                printf("        *                                     *\n");
                printf("        *       0 退出                        *\n");
                printf("        =======================================\n");
                break;
            }
            else
            {
                title(MAIN);
                printf("两次密码不一致请重新输入 回车键退出\n");
                printf("        =======================================\n");
                printf("        *       1 添加用户                    *\n");
                printf("        *                                     *\n");
                printf("        *       0 退出                        *\n");
                printf("        =======================================\n");
                printf("请输入用户名:%s\n",user[user_amount].name);
            }
         }
    }
}

void add_book()             //添加图书
{
    int tmp;
    title(MAIN);
    printf("        =======================================\n");
    printf("        *       1 添加图书                    *\n");
    printf("        *                                     *\n");
    printf("        *       0 退出                        *\n");
    printf("        =======================================\n");
    Book=fopen("books.txt","a");
    while(_getch()  != '0' )
    {
        temp = (point)malloc(sizeof(book));
        printf("请输入书名:");
        gets(temp->name);
        printf("请输入作者:");
        gets(temp->author);
        printf("请输入价格:");
        scanf("%lf",&temp->price);
        temp->lendable=TRUE;             //更新图书数据文件
        fprintf(Book,"%s\n%s\n%.2lf\n%d\n",temp->name,temp->author,temp->price,temp->lendable);
        title(MAIN);
        printf("图书添加成功\n");
        printf("        =======================================\n");
        printf("        *       1 继续添加                    *\n");
        printf("        *                                     *\n");
        printf("        *       0 退出                        *\n");
        printf("        =======================================\n");
        Tail->next=temp;
        Tail=temp;
    }
    fclose(Book);
}

void del_book()             //删除图书
{
    char tmp[NAME_LENTH];
    point str,pre;
    title(DEL_BOOK);
    printf("请输入你要删除的图书:");
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
                Book=fopen("books.txt","w");        //更新图书数据文件
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
            printf("该图书不存在 请重新输入:");
        }
        else
        {
            title(DEL_BOOK);
            printf("图书删除成功 回车键退出 继续删除请输入书名:\n");
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

void title(tmp)             //打印标题头
{
    system("CLS");
    printf("欢迎使用江西师大图书管理系统!\n\n");
    switch (tmp)
    {
        case DEL_USER:
            printf("小型图书管理系统---->删除用户\n");
            break;
        case INIT_PWD:
            printf("小型图书管理系统---->重置密码\n");
            break;
        case SIGN_IN:
            printf("小型图书管理系统---->用户登录\n");
            break;
        case DEL_BOOK:
            printf("小型图书管理系统---->删除图书\n");
            break;
    }
    if (tmp != MAIN)
        printf("=============================\n");
}

void list_user()            //列出所有用户
{
        title(MAIN);
        printf("=============================\n\n");
        for (int i = 0 ; i < user_amount ; i ++)
             printf("%d、  %s \n",i+1,user[i].name);
        getchar();
}

void del_user()             //删除用户
{
    char tmp[NAME_LENTH];
    int i;
    title(DEL_USER);
    printf("请输入你要删除的用户:");
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
            printf("用户删除成功！\n继续删除请输入用户名(输入0退出):");
        }
        else
        {
            title(DEL_USER);
            printf("用户名未找到！\n请重新输入(输入0退出):");
        }
    }
}

void init_password()        //初始化非管理员用户密码
{
    for (int t = 0 ; t < user_amount ; t ++ )       //更新用户密码
        if (user[t].user_type != SYSTEM)
            for (int i = '1' ; i < '9' ; i ++ )
                user[t].password[i-48] = i;
    update_user();           //更新用户数据文件
    init_all();
}

int change_password()       //更改当前用户密码
{
    char *tmp,*pass;
    title(INIT_PWD);
    printf("请输入当前用户密码:");
    pass = get_password();                  //获取当前密码
    while(1)
    {
        if ((strcmp(user[current_user].password,pass))==0)
        {
            printf("\n请输入新密码:");
            pass=get_password();            //获取新密码
            printf("\n请确认密  码:");
            tmp=get_password();             //确认新密码
            if (strcmp(tmp,pass)==0)
            {
                strcpy(user[current_user].password,tmp);    //跟新用户密码
                update_user();                              //更新数据文件
                printf("\n重置密码成功,请重新登录。");
                _getch();
                getchar();
                return TRUE;
            }
            else
            {
                printf("\n重置密码失败(两次密码不一致),请重新输入:");
                title(INIT_PWD);
            }
        }
        else
        {
            title(INIT_PWD);
            printf("\n重置密码失败(密码错误),请重新输入(输入0退出):");
            pass=get_password();
            if(pass[0] == '0' && pass[1] == '\0')
                return FAULSE;
        }
    }
}

void back_up()              //备份数据文件
{
    int t;
    FILE * user_text;
    FILE * book_text;
    user_text=fopen("pwd_.bk","wb");         //备份图书信息
    for ( t = 0 ; t < user_amount ; t ++ )
        fprintf(user_text,"%s\n%s\n%d\n",user[t].name,user[t].password,user[t].user_type);
    fclose(user_text);

    book_text=fopen("book_.bk","wb");        //备份用户信息
    for(temp=Head; temp != NULL; temp=temp->next)
        fprintf(book_text,"%s\n%s\n%.2lf\n%d\n",temp->name,temp->author,temp->price,temp->lendable);
    fclose(book_text);
}

void update_book()          //更新图书数据文件
{

}

void update_user()          //更新用户数据文件
{
    FILE *user_text=fopen("pwd.bd","rb");
    int t=0,i=0;
    while (!feof(user_text))                                   //读取用户信息
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

