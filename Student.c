#pragma warning(disable:4996)
#include <stdio.h>
#include <mysql.h>
#include <conio.h>
#include <stdlib.h>
#include <errno.h>



MYSQL* conn;
struct student
{
    int rollno;
    char name[50];
    int p_marks, c_marks;
    float per;
    char grade;
}st;
void write_student()
{
    char buff[255];

    printf("\nPlease Enter The New Details of student \n");
    printf("\nEnter The roll number of student ");
    scanf_s("%d", &st.rollno);
    getchar(); // flushing buffer
    printf("\n\nEnter The Name of student ");
    gets_s(st.name, sizeof(st.name));
    printf("\nEnter The marks in physics out of 100 : ");
    scanf_s("%d", &st.p_marks);
    printf("\nEnter The marks in chemistry out of 100 : ");
    scanf_s("%d", &st.c_marks);

    st.per = (st.p_marks + st.c_marks) / 2.0;
    if (st.per >= 60)
        st.grade = 'A';
    else if (st.per >= 50 && st.per < 60)
        st.grade = 'B';
    else if (st.per >= 33 && st.per < 50)
        st.grade = 'C';
    else
        st.grade = 'F';


    sprintf(buff, "insert into student values (%d, \'%s\', %d, %d, %f, \'%c\')", st.rollno, st.name, st.p_marks, st.c_marks, st.per, st.grade);
    mysql_query(conn, buff);
    printf("\n\nStudent Record Has Been Created.  Press any key.... ");
    _getch();
}
void display_all()
{

    system("cls");
    printf("\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n");
    printf("=========================================================================\n");
    printf("        R.No.      Name           P          C         Ave        Grade\n");
    printf("=========================================================================\n");

    int k;
    MYSQL_RES* sql_result;
    MYSQL_ROW row;
    int field;
    mysql_set_character_set(conn, "euckr");
    mysql_query(conn, "select * from student");
    sql_result = mysql_store_result(conn);
    field = mysql_num_fields(sql_result);
    while ((row = mysql_fetch_row(sql_result)))
    {
        for (k = 0; k < field; k++)
            printf("%12s", row[k]);
        printf("\n");
    }
    mysql_free_result(sql_result);
    _getch();
}


//***************************************************************
//        function to read specific record from file
//****************************************************************


void display_sp()
{
    int j;
    char buff2[255];
    char name[20];

    MYSQL_RES* sql_result;
    MYSQL_ROW row;
    int field;

    printf("Insert Name : ");
    scanf("%s", name);
    sprintf(buff2, "select * from student where name = '%s'", name);
    mysql_set_character_set(conn, "euckr");
    mysql_query(conn, buff2);
    sql_result = mysql_store_result(conn);
    field = mysql_num_fields(sql_result);
    printf("\n\n\n\t\tDISPLAY        RECORD !!!\n\n");
    printf("=========================================================================\n");
    printf("        R.No.      Name           P          C         Ave        Grade\n");
    printf("=========================================================================\n");
    while ((row = mysql_fetch_row(sql_result)))
    {
        for (j = 0; j < field; j++)
            printf("%12s", row[j]);
        printf("\n");
    }
    mysql_free_result(sql_result);
    _getch();
}
//***************************************************************
//        function to modify record of file
//****************************************************************


void modify_student()
{
    int no, i;
    char md = 0;
    char buff3[255];
    char na[50];
    system("cls");
    printf("\n\n\tTo Modify ");
    printf("\n\n\tPlease Enter The roll number of student");
    scanf_s("%d", &no);
    system("cls");
    printf("\n\n\t1.Rollno");
    printf("\n\n\t2.Name");
    printf("\n\n\t3.P_marks");
    printf("\n\n\t4.C_marks");
    printf("\n\n\t5.Per");
    printf("\n\n\t6.Grade");
    printf("\n\n\tChoose what you want to modify.(1-6)");
    md = _getch();
    switch (md)
    {
    case '1':   system("cls");
        printf("\n\n\tHow do you want it fixed?:");
        scanf("%d", &i);
        sprintf(buff3, "update student set rollno = %d where rollno = %d", i, no);
        mysql_query(conn, buff3); 
        printf("\n\n\t Record Updated. Press any key....");
        break;
    case '2':system("cls");
        printf("\n\n\tHow do you want it fixed?:");
        scanf("%s", &na);
        sprintf(buff3, "update student set name = '%s' where rollno = %d", na, no);
        mysql_query(conn, buff3);
        printf("\n\n\t Record Updated. Press any key....");
        break;
    case '3':   system("cls");
        printf("\n\n\tHow do you want it fixed?:");
        scanf("%d", &i);
        sprintf(buff3, "update student set p_marks = %d where rollno = %d", i, no);
        mysql_query(conn, buff3);
        printf("\n\n\t Record Updated. Press any key....");
        break;
    case '4': system("cls");
        printf("\n\n\tHow do you want it fixed?:");
        scanf("%d", &i);
        sprintf(buff3, "update student set c_marks = %d where rollno = %d", i, no);
        mysql_query(conn, buff3);
        printf("\n\n\t Record Updated. Press any key....");
        break;
    case '5':system("cls");
        printf("\n\n\tHow do you want it fixed?:");
        scanf("%d", &i);
        sprintf(buff3, "update student set per = %d where rollno = %d", i, no);
        mysql_query(conn, buff3);
        printf("\n\n\t Record Updated. Press any key....");
        break;
    case '6':system("cls");
        printf("\n\n\tHow do you want it fixed?:");
        scanf("%s", &na);
        sprintf(buff3, "update student set grade = '%s' where rollno = %d", na, no);
        mysql_query(conn, buff3);
        printf("\n\n\t Record Updated. Press any key....");
        break;
    default:   printf("\a");
    }

    _getch();
}


//***************************************************************
//        function to delete record of file
//****************************************************************


void delete_student()
{
    int no;

    system("cls");
    printf("\n\n\n\tDelete Record");
    printf("\n\nPlease Enter The roll number of student You Want To Delete");
    scanf("%d", &no);

    char buff4[255];
    sprintf(buff4, "delete from student where rollno = %d", no);
    mysql_query(conn, buff4);

    printf("\n\n\tRecord Deleted ..");
    _getch();
}



//***************************************************************
//        THE MAIN FUNCTION OF PROGRAM
//****************************************************************


void main()
{
    char ch;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "hansung", "studentdb", 0, NULL, 0))
    {
        printf("%s\n", mysql_error(conn));
        exit(1);
    }
    do
    {
        system("cls");

        printf("\n\n\t1.CREATE STUDENT RECORD");
        printf("\n\n\t2.DISPLAY ALL STUDENTS RECORDS");
        printf("\n\n\t3.SEARCH STUDENT RECORD ");
        printf("\n\n\t4.MODIFY STUDENT RECORD");
        printf("\n\n\t5.DELETE STUDENT RECORD");
        printf("\n\n\t6.EXIT");
        printf("\n\n\tPlease Enter Your Choice (1-6) ");
        ch = _getche();

        switch (ch)
        {
        case '1':   system("cls");
            write_student();
            break;
        case '2':   display_all();
            break;
        case '3':   system("cls");
            display_sp();
            break;
        case '4':   modify_student(); break;
        case '5':   delete_student(); break;
        case '6':   break;
        default:   printf("\a");
        }
    } while (ch != '6');
    mysql_close(conn);
}