#include "processor.hpp"
#include "algorithms.hpp"
#include "sqlite_handler.hpp"

void processer::tf()
{
    // External Clases
    algorithm algo;
    sqlite_hand sql;
    int id = -1;

    id = sql.id_request();
    if (!(id != -1)) {
        std::cerr << "\x1B[31m[ERROR]\033[0m" << " No unprocessed row found." << std::endl;
        

    }
    
    // Query SQL pour récupérer un lien et le texte assemblée 
    // (Titre + sous-titre + texte) D'une meme row choisie au hasard dans la table website.
    sql.update_request(id);
    std::string link = sql.select_link(id);
    std::string content = sql.select_request(id);

    // Utilisation d'algorithmes pour récupérer le nombre total de mots dans le texte et le nombre d'occurences de chaque mot dans le texte.
    int word_number = algo.word_counter(content);
    std::unordered_map<std::string, int> words = algo.word_occurences(content);

    // itération dans la hashmap contenant le nombre d'occurences de chaque mot.
    for(auto i : words) {
        
        // Application de la méthode TF (Term frequency (Nombre total de mot x nombre d'occurence de ce mot))
        int score = i.second * word_number;

        // Sauvegarde du résultat dans la table rev_index pour l'indexation inversée de l'API.
        sql.insert_rev_index(i.first, link, score);
        
    }
    
    // Fermeture la base de données
    sqlite3_close(sql.DB);



}