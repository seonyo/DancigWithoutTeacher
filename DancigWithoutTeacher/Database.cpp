#include "Database.h"
#include <cstdio>

MYSQL Conn;
MYSQL* ConnPtr;
int Stat;
MYSQL_RES* Result;
MYSQL_ROW Row;

bool connectToDatabase() {
    mysql_init(&Conn);

    //한글 깨짐 지원
    mysql_options(&Conn, MYSQL_SET_CHARSET_NAME, "euckr");

    //데이터베이스 연결
    ConnPtr = mysql_real_connect(&Conn, "localhost", "root", "990327", "DancingWithoutTeacher", 3306, (char*)NULL, 0);

    //데이터베이스 연결 여부
    if (ConnPtr == NULL) {
        fprintf(stderr, "MySQL connection error: %s", mysql_error(&Conn));
        return false;
    }
    else {
        printf("Connection successful...\n");
        return true;
    }
}

//데이터베이스 종료 함수
void closeDatabase() {
    mysql_close(ConnPtr);
}
