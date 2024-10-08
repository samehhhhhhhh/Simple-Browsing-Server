#ifndef PROCESSING_HPP
#define PROCESSING_HPP

#include "includes.hpp"

static int callback_id(void* data, int argc, char** argv, char** azColName) {
    int* id = static_cast<int*>(data);

    if (argc >= 1) {
        *id = argv[0] ? std::stoi(argv[0]) : -1;
    } else {
        std::cerr << "No ID retrieved" << std::endl;
    }

    return 0;
}

static int callback_string(void* data, int argc, char** argv, char** azColName) {
    std::string* result = static_cast<std::string*>(data);

    if (argc >= 3) {
        std::string title = argv[0] ? argv[0] : "";
        std::string subtitles = argv[1] ? argv[1] : "";
        std::string text = argv[2] ? argv[2] : "";

        *result = title + " " + subtitles + " " + text;
    } else {
        std::cerr << "Not enough columns retrieved" << std::endl;
    }

    return 0;
}
static int callback_link(void* data, int argc, char** argv, char** azColName) {
    std::string* result = static_cast<std::string*>(data);

    
    if (argc == 1 && argv[0]) {
        *result = argv[0];
    } else {
        std::cerr << "\x1B[31m[ERROR]\033[0m" << "Unexpected number of columns returned" << std::endl;
        return 1;
    }

    return 0; 
}

class sqlite_hand {

public:

    // D�claration de la base de donn�e.
    sqlite3* DB;
    
    // D�claration de variables repr�santants le contenu des tables SQL.
    std::string sql_website_table = "CREATE TABLE IF NOT EXISTS `websites` ("
    "`ID` INTEGER PRIMARY KEY AUTOINCREMENT,"
    "`Linked` TEXT(10000),"
    "`Text` TEXT(100000),"
    "`Subtitles` TEXT(800),"
    "`Title` TEXT(100),"
    "`Link` TEXT(100),"
    "`PROCESSED` TEXT DEFAULT 'false'"
    ");";

    std::string sql_reserverindex_table = "CREATE TABLE IF NOT EXISTS `reverseindex` ("
        "`Word` TEXT(50) NOT NULL,"
        "`Link` TEXT(100) NOT NULL,"
        "`Score` INT(30) NOT NULL"
        ");";

    std::string sql_crawlerlinks_table = "CREATE TABLE IF NOT EXISTS `waitlist` ("
        "`Link` TEXT(100) NOT NULL"
        ");";

    // Variables SQL.
    int exit;
    char* messagerr;
    
    std::string result;
    char* errMsg = 0;

    // Fonctions de la classe.

    int id_request();

    void update_request(int& id);

    std::string select_request(int& id);

    void insert_rev_index(std::string word, std::string link, int score);

    std::string select_link(int& id);


    // Constructeur
    sqlite_hand() {
        
        // Ouverture de la base de donnée.
        exit = sqlite3_open("database.db", &DB);

        // Verification / Création des tables SQL
        exit = sqlite3_exec(DB, sql_website_table.c_str(), NULL, 0, &messagerr);
        exit = sqlite3_exec(DB, sql_crawlerlinks_table.c_str(), NULL, 0, &messagerr);
        exit = sqlite3_exec(DB, sql_reserverindex_table.c_str(), NULL, 0, &messagerr);

        // Verification de l'initialisation.
        if (exit != SQLITE_OK) {
            std::cerr << "Error Connnecting : " << messagerr <<std::endl;
            sqlite3_free(messagerr);
        }

        else
            std::cout << "Initialisation succesful" << std::endl;   
    }
 
};

#endif