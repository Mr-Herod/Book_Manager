#include <manager.h>

int  search_book();    //����ͼ��
void student();        //ѧ��ģ��
void teacher();        //��ʦģ��
void manager();        //ͼ�����Աģ��
void sys();            //ϵͳ����Աģ��
void test();           //���Խӿ�

int main()
{
//  test();
    init_all();                         //��ʼ������
    int user;
    char opt;
    while (1)
    {
        print_menu(INIT);               //��ӡ�˵�
        opt=_getch();                   //��ȡ����
        if ( opt == '1' )
        {
           system("CLS");
           user=login();                //�û���½
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
                printf("\n�ڴ��´�ʹ�ã��ټ�!");
                return 0;
         }
         else
         {
                printf("\n��ѡ���¼ϵͳ�����˳�ϵͳ\n���������������");
                _getch();
         }
    }
}

void sys()
{
    char opt;
    while (1)
    {
        print_menu(SYSTEM);             //��ӡ�˵�
        opt=_getch();                   //��ȡ�û�ѡ��
        switch (opt)
        {
            case '1':
                list_user();break;          //��ʾ�����û�
            case '2':
                add_user();break;           //����û�
            case '3':
                del_user();break;           //ɾ���û�
            case '4':
                list_book(ALL);break;       //��ʾ����ͼ��
            case '5':
                del_book();break;           //ɾ��ͼ��
            case '6':
                add_book();break;           //���ͼ��
            case '7':
                init_password();break;      //��ʼ���û�����
            case '8':
                if (change_password())      //�޸�����
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
        print_menu(STUDENT);            //��ӡ�˵�
        opt=_getch();                   //��ȡ�û�ѡ��
        switch (opt)
        {
            case '1':
                list_book(ALL);break;   //�г�����ͼ��
            case '5':
                if (change_password())  //�޸�����
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
        print_menu(TEACHER);            //��ӡ�˵�
        opt=_getch();                   //��ȡ�û�ѡ��
        switch (opt)
        {
            case '1':
                list_book(ALL);break;   //�г�����ͼ��
            case '6':
                if (change_password())  //�޸�����
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
        print_menu(MANAGER);            //��ӡ�˵�
        opt=_getch();                   //��ȡ�û�ѡ��
        switch (opt)
        {
            case '1':
                list_book(ALL);break;   //�г�����ͼ��
            case '6':
                add_book();break;       //���ͼ��
            case '7':
                if (change_password())  //�޸�����
                    return;
                break;
            case '0':
                return;
            default:
                return;
        }
    }
}

void test()            //���Խӿ�
{
    FILE * user_text;
    int t=0;
    int i=0;
    int j=0;
    user_text=fopen("pwd.txt","r");
    while (fscanf(user_text,"%s",&user[user_amount].name) != EOF)                //��ȡ�û���Ϣ
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
    user_text=fopen("pwd.bd","wb");           //���������ļ�
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
    while (!feof(user_text))                                   //��ȡ�û���Ϣ
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


