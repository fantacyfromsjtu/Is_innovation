#include <sqlite3.h>
#include <iostream>
#include <string>

int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

int main(int argc, char* argv[]) {
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    // 打开数据库
    rc = sqlite3_open("pattern_database.db", &db);
    if (rc) {
        std::cerr << "无法打开数据库: " << sqlite3_errmsg(db) << std::endl;
        return 0;
    } else {
        std::cout << "数据库打开成功" << std::endl;
    }

    // 准备 SQL 查询
    const char* sql = "SELECT * FROM patterns;";

    // 执行 SQL 查询
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL 错误: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "查询成功执行" << std::endl;
    }

    // 关闭数据库
    sqlite3_close(db);

    return 0;
}