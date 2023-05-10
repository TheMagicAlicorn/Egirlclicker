#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sqlite3.h>
#include "db.h"

sqlite3 *db;
sqlite3_stmt* stmtUpdate, * stmtInsert;

uint64_t savedEgirls;
uint64_t savedDaddy;
uint64_t savedCatears;

int rc;

static int callback(void *data, int argc, char **argv, char **azColName){ 
   savedEgirls = atoi(argv[0]);
   savedDaddy = atoi(argv[1]);
   savedCatears = atoi(argv[2]);
   return 0;
}

int db_init(){
    char *errMsg = 0;
    const char* data;

    rc = sqlite3_open("save.db", &db);
   
    const char *sql = "CREATE TABLE IF NOT EXISTS egirls (id INTEGER PRIMARY KEY AUTOINCREMENT, savetime DATETIME, egirls BIG INT UNSIGNED, daddy BIG INT UNSIGNED, catears BIG INT UNSIGNED)";
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);

    const char *sqlSave = "SELECT egirls, daddy, catears FROM egirls WHERE id = (SELECT MAX(id) FROM egirls)";
    rc = sqlite3_exec(db, sqlSave, callback, (void*)data, &errMsg);

    const char *sqlInsert = "INSERT INTO egirls (egirls, daddy, catears, savetime) VALUES (?, ?, ?, CURRENT_TIMESTAMP)";
    rc = sqlite3_prepare_v2(db, sqlInsert, -1, &stmtInsert, NULL);

    const char *sqlUpdate = "UPDATE egirls SET egirls = ?, daddy = ?, catears = ?,savetime = CURRENT_TIMESTAMP WHERE id = (SELECT MAX(id) FROM egirls)";
    rc = sqlite3_prepare_v2(db, sqlUpdate, -1, &stmtUpdate, NULL);

    db_newsave(0, 0, 0);
    return 0;
}

int db_save(uint64_t egirls, uint64_t daddy, uint64_t catears){
    sqlite3_bind_int64(stmtUpdate, 1, egirls);
    sqlite3_bind_int64(stmtUpdate, 2, daddy);
    sqlite3_bind_int64(stmtUpdate, 3, catears);

    rc = sqlite3_step(stmtUpdate);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Error preparing SQL statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_reset(stmtUpdate);
    return 0;
}

int db_newsave(uint64_t egirls, uint64_t daddy, uint64_t catears){
    sqlite3_bind_int64(stmtInsert, 1, egirls);
    sqlite3_bind_int64(stmtInsert, 2, daddy);
    sqlite3_bind_int64(stmtInsert, 3, catears);

    rc = sqlite3_step(stmtInsert);
    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Error preparing SQL statement: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_reset(stmtInsert);
    return 0;
}

int db_close(){
    sqlite3_finalize(stmtUpdate);
    sqlite3_finalize(stmtInsert);
    sqlite3_close(db);
    return 0;
}