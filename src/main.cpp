#include "includes.hpp"
#include "sqlite_handler.hpp"
#include "algorithms.hpp"
#include "sqlite3.h"
#include <iostream>
#include <string>



int main() {
    sqlite_hand sql;
    algorithm algo;
    
    
    

    // Exécuter la requête SQL
    
    int id = sql.id_request();
    sql.update_request(id);
    sql.select_request(id);
    

    

    // Fermer la base de données
    sqlite3_close(sql.DB);

    return 0;
}
