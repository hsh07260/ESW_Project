#include <stdio.h>
#include <stdlib.h>
#include "/usr/include/mysql/mysql.h"
#include <string.h>

void finish_with_error(MYSQL *conn)
{
  fprintf(stderr, "%s\n",mysql_error(conn));
  mysql_close(conn);
  exit(1);
}

int main(int argc, char *argv[])
{

  MYSQL *conn;
  conn = mysql_init(NULL);

  if( conn == NULL )
  {
    printf("init fail\n");
    fprintf(stderr, "mysql_init() fail\n");
    exit(1);
  }

  if( mysql_real_connect(conn, "localhost", NULL, "123456", "SalBBAE", 0, NULL,0)==NULL)
  {
    printf("connect error\n");
    finish_with_error(conn);
  }

  //if(mysql_query(conn, "SELECT * FROM kcal_table"))
  if(mysql_query(conn, "SELECT * FROM record"))
  {
    printf("query error\n");
    finish_with_error(conn);
  }

  MYSQL_RES *result;
  MYSQL_FIELD *fields;
  result = mysql_store_result(conn);
  if (result == NULL)
  {
    printf("result error\n");
    finish_with_error(conn);
  }
  int num_fields = mysql_num_fields(result);
  MYSQL_ROW row;
  fields = mysql_fetch_fields(result);
  printf("%s\n",fields[1].name);

  //char *milk = "milk";
  char * m1 = "123";
  while(row = mysql_fetch_row(result))
  {
    //if(strcmp("milk",row[0]) == 0)
    //if(strcmp(milk,row[0]) == 0)
    if(strcmp(m1,row[1])==0)
    //if(strcmp(m1,row[0]) == 0)
    {
      printf("%s is %s \n",m1,row[1]);
      //printf("%s 's kcal is %d\n",row[0],atoi(row[1]));
    }
    //printf("row   %s\n",row[0]);
    //printf("row  %d\n",atoi(row[1]));
    //printf("\n");
  }

  mysql_free_result(result);
  mysql_close(conn);
  return 0;
}
