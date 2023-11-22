#pragma once

#ifndef DATABASE_H
#define DATABASE_H

#include <mysql.h>

extern MYSQL Conn;
extern MYSQL* ConnPtr;
extern int Stat;
extern MYSQL_RES* Result;
extern MYSQL_ROW Row;

bool connectToDatabase();
void closeDatabase();

#endif