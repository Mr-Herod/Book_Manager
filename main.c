#include <manager.h>

int  search_book();    //查找图书
void student();        //学生模块
void teacher();        //教师模块
void manager();        //图书管理员模块
void sys();            //系统管理员模块
void test();           //调试接口

int main()
{
//  test();
    init_all();                         //初始化数据
    int user;
    char opt;
    while (1)
    {
        print_menu(INIT);               //打印菜单
        opt=_getch();                   //获取输入
        if ( opt == '1' )
        {
           system("CLS");
           user=login();                //用户登陆
           switch (user)
           {
               case STUDENT:
                    student();break;
               case TEACHER:
                    teacher();break;
               case MANAGER:
                    manager();break;
               case SYSTEM:
                    sys();break;
            }
         }
         else if (opt == '0')
         {
                printf("\n期待下次使用，再见!");
                return 0;
         }
         else
         {
                printf("\n请选择登录系统或者退出系统\n按任意键重新输入");
                _getch();
         }
    }
}

void sys()
{
    char opt;
    while (1)
    {
        print_menu(SYSTEM);             //打印菜单
        opt=_getch();                   //获取用户选项
        switch (opt)
        {
            case '1':
                list_user();break;          //显示所有用户
            case '2':
                add_user();break;           //添加用户
            case '3':
                del_user();break;           //删除用户
            case '4':
                list_book(ALL);break;       //显示所有图书
            case '5':
                del_book();break;           //删除图书
            case '6':
                add_book();break;           //添加图书
            case '7':
                init_password();break;      //初始化用户密码
            case '8':
                if (change_password())      //修改密码
                    return;
                break;
            case '9':
                return;
            default:
                return;
        }
    }
}

void student()
{
    char opt;
    while (1)
    {
        print_menu(STUDENT);            //打印菜单
        opt=_getch();                   //获取用户选项
        switch (opt)
        {
            case '1':
                list_book(ALL);break;   //列出所有图书
            case '5':
                if (change_password())  //修改密码
                    return;
                break;
            case '0':  break;
            default:   break;
        }
    }
}

void teacher()
{
    char opt;
    while (1)
    {
        print_menu(TEACHER);            //打印菜单
        opt=_getch();                   //获取用户选项
        switch (opt)
        {
            case '1':
                list_book(ALL);break;   //列出所有图书
            case '6':
                if (change_password())  //修改密码
                    return;
                break;
            case '0':
                return;
            default:
                return;
        }
    }
}

void manager()
{
    char opt;
    while (1)
    {
        print_menu(MANAGER);            //打印菜单
        opt=_getch();                   //获取用户选项
        switch (opt)
        {
            case '1':
                list_book(ALL);break;   //列出所有图书
            case '6':
                add_book();break;       //添加图书
            case '7':
                if (change_password())  //修改密码
                    return;
                break;
            case '0':
                return;
            default:
                return;
        }
    }
}

void test()            //调试接口
{
    FILE * user_text;
    int t=0;
    int i=0;
    int j=0;
    user_text=fopen("pwd.txt","r");
    while (fscanf(user_text,"%s",&user[user_amount].name) != EOF)                //读取用户信息
    {
        fscanf(user_text,"%s",&user[user_amount].password);
        fscanf(user_text,"%d",&user[user_amount++].user_type);
    }
    fclose(user_text);
    for (t = 0 ; t < user_amount ; t ++ )
    {
        for (i = 0 ; i < 16 ; i ++ )
            if (user[t].name[i] == '\0')
                for (j = i+1 ; j < 16 ; j ++ )
                    user[t].name[j] = '\0';
        for (i = 0 ; i < 16 ; i ++ )
            if (user[t].password[i] == '\0')
                for (j = i+1 ; j < 16 ; j ++ )
                    user[t].password[j] = '\0';
    }
    user_text=fopen("pwd.bd","wb");           //更新数据文件
    for (t = 0 ; t < user_amount ; t ++ )
    {
        for (i = 0 ; i < 16 ; i ++ )
            user[t].name[i] += SECURE;
        for (j = 0 ; j < 16 ; j ++ )
            user[t].password[j] += SECURE;
        user[t].user_type += SECURE;
        fwrite(user[t].name,sizeof(user[t].name),1,user_text);
        fwrite(user[t].password,sizeof(user[t].password),1,user_text);
        fwrite(&user[t].user_type,sizeof(int),1,user_text);
    }
    fclose(user_text);
    user_text=fopen("pwd.bd","rb");
    t=0;
    while (!feof(user_text))                                   //读取用户信息
    {
        fread(user[t].name,sizeof(user[t].name),1,user_text);
        fread(user[t].password,sizeof(user[t].password),1,user_text);
        fread(&user[t].user_type,sizeof(int),1,user_text);
        for (i = 0 ; i < 16 ; i ++ )
            user[t].name[i] -= SECURE;
        for (j = 0 ; j < 16 ; j ++ )
            user[t].password[j] -= SECURE;
        user[t].user_type -= SECURE;
        t++;
    }
    fclose(user_text);
    for (t = 0 ; t < user_amount ; t ++ )
    {
        printf("%s\n%s\n%d\n",user[t].name,user[t].password,user[t].user_type);
    }
    for (t = 0 ; t < user_amount ; t ++ )
    {
        for (i = 0 ; i < 16 ; i ++ )
            printf("%d ",user[t].name[i]);
        for (i = 0 ; i < 16 ; i ++ )
            printf("%d ",user[t].password[i]);
    }
 //   exit(0);
}


