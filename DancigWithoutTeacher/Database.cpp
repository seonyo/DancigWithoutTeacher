#include "Database.h"
#include <cstdio>

MYSQL Conn;
MYSQL* ConnPtr;
int Stat;
MYSQL_RES* Result;
MYSQL_ROW Row;

bool connectToDatabase() {
    mysql_init(&Conn);

    //ÇÑ±Û ±úÁü Áö¿ø
    mysql_options(&Conn, MYSQL_SET_CHARSET_NAME, "euckr");

    ConnPtr = mysql_real_connect(&Conn, "localhost", "root", "990327", "DancingWithoutTeacher", 3306, (char*)NULL, 0);

    if (ConnPtr == NULL) {
        fprintf(stderr, "MySQL connection error: %s", mysql_error(&Conn));
        return false;
    }
    else {
        printf("Connection successful...\n");
        return true;
    }
}

void closeDatabase() {
    mysql_close(ConnPtr);
}
