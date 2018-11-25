#include <stdio.h>
#include <stdlib.h>
#include "/usr/include/mysql/mysql.h"

int main(int argc, char *argv[])
{

  MYSQL *conn;
  mysql_init(NULL);

  if( conn == NULL )
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(1);
  }

  if( mysql_real_connect(conn, "localhost", "dongho", "123456", "SalBBAE", 0, NULL, 0) == NULL )
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
  }

  if( mysql_query(conn, "CREATE DATABASE SalBBAE") )
  {
    fprintf(stderr, "%s\n", mysql_error(conn));
    mysql_close(conn);
    exit(1);
  }

  mysql_close(conn);
  exit(0);

}
