from flask import Flask, render_template, request
import sqlite3

app = Flask(__name__)

def search_links(database_path, query):
    # Séparer la requête en mots distincts
    words = query.split()
    
    # Construire une requête SQL dynamique en fonction des mots
    placeholders = ', '.join('?' for word in words)
    query_sql = f"""
    SELECT link, SUM(score) as total_score
    FROM reverseindex
    WHERE word IN ({placeholders})
    GROUP BY link
    ORDER BY total_score DESC
    LIMIT 50
    """
    
    # Connexion à la base de données SQLite
    conn = sqlite3.connect(database_path)
    cursor = conn.cursor()
    
    # Exécuter la requête avec les mots de la requête
    cursor.execute(query_sql, words)
    top_links = cursor.fetchall()
    
    # Fermer la connexion à la base de données
    conn.close()
    
    return top_links

@app.route('/')
def search_page():
    return render_template('search.html')

@app.route('/results', methods=['GET'])
def results():
    # Récupérer la chaîne de recherche de l'utilisateur
    query = request.args.get('query')
    
    if query:
        # Chemin vers la base de données SQLite
        database_path = "database.db"
        
        # Rechercher les meilleurs liens
        top_links = search_links(database_path, query)
        
        # Rendre le template avec les résultats
        return render_template('results.html', top_links=top_links)
    else:
        return "No query provided.", 400

if __name__ == '__main__':
    app.run(debug=True)
