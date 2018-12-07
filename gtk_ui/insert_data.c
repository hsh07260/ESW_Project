#include <stdio.h>
#include <stdlib.h>
#include "/usr/include/mysql/mysql.h"
#include <string.h>

void func_insert(char * date, char *m1,char *m2,char *m3,char *l1,char *l2,char *l3,char *d1,char *d2,char *d3,char *tocal, char *weight, char *comment, char *data1,char *data2,char *data3,char *data4,char *data5,char *data6,char *data7,char *data8,char *data9,char *data10,char *data11,char *data12,char *data13)
{
  char query[255];

  MYSQL *conn;
  conn = mysql_init(NULL);

  if( mysql_real_connect(conn, "localhost", NULL, "123456", "SalBBAE", 0, NULL,0)==NULL)
  {
    printf("connect error\n");
  }
  sprintf(query,"insert into record(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s) values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')", date,m1,m2,m3,l1,l2,l3,d1,d2,d3,tocal,weight,comment,data1,data2,data3,data4,data5,data6,data7,data8,data9,data10,data11,data12,data13);
  //printf("%s %s \n",field, data);
  if(mysql_query(conn, query))
  {
    printf("query error\n");
  }

  mysql_close(conn);
  exit(0);
}
