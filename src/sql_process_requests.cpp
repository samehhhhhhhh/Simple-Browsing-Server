
#include "sqlite_handler.hpp"

int sqlite_hand::id_request() 
{
    int selected_id = 1;
	exit = sqlite3_exec(DB, sql_query_get_id.c_str(), callback_id, &selected_id, &errMsg);
    if (exit != SQLITE_OK) {
        std::cerr << "\x1B[31m[ERROR]\033[0m" << " SQL error in SELECT ID: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else if (selected_id == -1) {
        std::cerr << "\x1B[31m[ERROR]\033[0m" << " No unprocessed row found." << std::endl;
        sqlite3_close(DB);
        
    }

    std::cout << "\x1B[32m[OK]\033[0m" << " Random Column selected" << std::endl;

    return selected_id;
    
}

void sqlite_hand::update_request(int& id) 
{

    std::string sql_query_update = 
        "UPDATE websites "
        "SET PROCESSED = 'true' "
        "WHERE ID = " + std::to_string(id) + ";";

	exit = sqlite3_exec(DB, sql_query_update.c_str(), nullptr, nullptr, &errMsg);
    if (exit != SQLITE_OK) {
        std::cerr << "\x1B[31m[ERROR]\033[0m" << "SQL error in UPDATE: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }

    std::cout << "\x1B[32m[OK]\033[0m" << " Succesfully updated column." << std::endl;
}

void sqlite_hand::select_request(int& id) 
{
    std::string sql_query_select = 
        "SELECT Title, Subtitles, Text FROM websites "
        "WHERE ID = " + std::to_string(id) + ";";

	exit = sqlite3_exec(DB, sql_query_select.c_str(), callback_string, &result, &errMsg);
    if (exit != SQLITE_OK) {
        std::cerr << "\x1B[31m[ERROR]\033[0m" << "SQL error in SELECT: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Assembled string: " << result << std::endl;
    }
}