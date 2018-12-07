#include <stdio.h>
#include <stdlib.h>
#include "/usr/include/mysql/mysql.h"
#include <string.h>

void func_insert(char *data1,char *data2,char *data3,char *data4,char *data5,char *data6,char *data7,char *data8,char *data9,char *data10)
{
  char query[1000];

  MYSQL *conn;
  conn = mysql_init(NULL);

  if( mysql_real_connect(conn, "localhost", NULL, "123456", "SalBBAE", 0, NULL,0)==NULL)
  {
    printf("connect error\n");
  }
  printf("connect success\n");
  sprintf(query,"INSERT INTO record (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s) values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')", "date","m1","m2","l1","l2","d1","d2","tocal","weight","comment",data1,data2,data3,data4,data5,data6,data7,data8,data9,data10);
  if(mysql_query(conn, query))
  {
    printf("query error\n");
  }

  mysql_close(conn);
  return;
}
