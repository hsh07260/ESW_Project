#include <stdio.h>
#include <stdlib.h>
#include "/usr/include/mysql/mysql.h"

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

  if( mysql_real_connect(conn, "localhost", NULL, "123456", "SalBBAE", 0, NULL,$
  {
    printf("connect error\n");
    finish_with_error(conn);
  }

  if(mysql_query(conn, "SELECT * FROM kcal_table"))
  {
    printf("query error\n");
    finish_with_error(conn);
  }





}
