#include <stdio.h>
#include <stdlib.h>
#include "/usr/include/mysql/mysql.h"
#include <string.h>

void func_remove(char *data)
{
  char remove_buf[100];
  MYSQL *conn;
  conn = mysql_init(NULL);

  if( mysql_real_connect(conn, "localhost", NULL, "123456", "SalBBAE", 0, NULL,0)==NULL)
  {
    printf("connect error\n");
  }
  printf("connect success\n");
  sprintf(remove_buf,"delete from record where date = '%s'",data);
  if(mysql_query(conn,remove_buf))
  {
    printf("remove query error\n");
  }
  mysql_close(conn);
  return;
}
