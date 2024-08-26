
#include "sqlite_handler.hpp"

int sqlite_hand::id_request() 

{
    // Query
    std::string sql_query_get_id = 
        "SELECT ID FROM websites "
        "WHERE PROCESSED = 'false' "
        "ORDER BY RANDOM() "
        "LIMIT 1;";

    int selected_id = -1;

    // Application de la query
	exit = sqlite3_exec(DB, sql_query_get_id.c_str(), callback_id, &selected_id, &errMsg);

    // Verification d'erreurs
    if (exit != SQLITE_OK) {
        std::cerr << "\x1B[31m[ERROR]\033[0m" << " SQL error in SELECT ID: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else if (selected_id == -1) {
        std::cerr << "\x1B[31m[ERROR]\033[0m" << " No unprocessed row found." << std::endl;
        
        sqlite3_close(DB);
        
    } else {
        std::cout << "\x1B[32m[OK]\033[0m" << " Random Column selected" << std::endl;
        
    }
    
    return selected_id;
    
}

void sqlite_hand::update_request(int& id) 

{

    // Query SQL
    std::string sql_query_update = 
        "UPDATE websites "
        "SET PROCESSED = 'true' "
        "WHERE ID = " + std::to_string(id) + ";";

    // Application de la query
	exit = sqlite3_exec(DB, sql_query_update.c_str(), nullptr, nullptr, &errMsg);

    // Verification d'erreur
    if (exit != SQLITE_OK) {
        std::cerr << "\x1B[31m[ERROR]\033[0m" << "SQL error in UPDATE: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else {
        std::cout << "\x1B[32m[OK]\033[0m" << " Succesfully updated column." << std::endl;
    }

}

std::string sqlite_hand::select_request(int& id) 

{

    // Query
    std::string sql_query_select = 
        "SELECT Title, Subtitles, Text FROM websites "
        "WHERE ID = " + std::to_string(id) + ";";

    // Application de la query
	exit = sqlite3_exec(DB, sql_query_select.c_str(), callback_string, &result, &errMsg);

    // Gestion des erreurs
    if (exit != SQLITE_OK) {
        std::cerr << "\x1B[31m[ERROR]\033[0m" << "SQL error in SELECT: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return "Error";
    } else {
        std::cout << "Assembled string: " << result << std::endl;
        return result;
    }
    
}

std::string sqlite_hand::select_link(int& id)

{
    // Query
    std::string sql_query_select_link = 
        "SELECT `Link` FROM websites "
        "WHERE ID = " + std::to_string(id) + ";";

    // Application de la query
	exit = sqlite3_exec(DB, sql_query_select_link.c_str(), callback_link, &result, &errMsg);

    // Gestion des erreurs
    if (exit != SQLITE_OK) {
        std::cerr << "\x1B[31m[ERROR]\033[0m" << "SQL error in SELECT LINK: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return "Error";
    } else {
        std::cout << "LINK: " << result << std::endl;
        return result;
    }

}

void sqlite_hand::insert_rev_index(std::string word, std::string link, int score)
{
    // Query
    std::string sql_query = 
    "INSERT INTO `reverseindex` (`Word`, `Link`, `Score`) VALUES ('" + word + "', '" + link + "', " + std::to_string(score) + ");";

    // Application de la query
    exit = sqlite3_exec(DB, sql_query.c_str(), NULL, 0, &errMsg);

    // Verification d'erreurs
    if (exit != SQLITE_OK) {
        std::cerr << "\x1B[31m[ERROR]\033[0m" << "SQL error in INSERT: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } 

}