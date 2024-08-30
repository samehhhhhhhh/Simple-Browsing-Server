import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin
import json
import concurrent.futures
import sqlite3
from colorama import Fore

def read_threads():
    with open('config.json', 'r') as json_file:
        json_object = json.load(json_file)
        return int(json_object['max_threads'])  
def web_scraper():
    
    conn = sqlite3.connect('database.db')
    try:
        res = conn.execute("SELECT * FROM waitlist ORDER BY RANDOM() LIMIT 1")
        url = res.fetchone()[0]  

        response = requests.get(url)

        if response.status_code == 200:
            soup = BeautifulSoup(response.content, 'html.parser')

            titles = ' '.join([title.get_text(strip=True) for title in soup.find_all(['h1'])])
            subtitles = ' '.join([subtitle.get_text(strip=True) for subtitle in soup.find_all(['h2', 'h3'])])
            text = ' '.join([p.get_text(strip=True) for p in soup.find_all('p')])

            links = []
            for a in soup.find_all('a', href=True):
                href = a['href']
                full_url = urljoin(url, href) if not href.startswith('http') else href
                if full_url not in links:
                    links.append(full_url)
            
            conn.execute("INSERT INTO websites (Linked, Text, Subtitles, Title, Link, PROCESSED) VALUES (?, ?, ?, ?, ?, ?)", 
                         (','.join(links), text, subtitles, titles, url, 'false'))
            
            for link in links:
                cursor = conn.execute("SELECT ID FROM websites WHERE Link = ?", (link,))
                cursor2 = conn.execute("SELECT Link FROM waitlist WHERE Link = ?", (link,))
                if cursor.fetchone() is None and cursor2.fetchone() is None:
                    conn.execute("INSERT INTO waitlist (Link) VALUES (?)", (link,))
            conn.execute("DELETE FROM waitlist WHERE Link = ?", (url,))
            conn.commit()
            
            return {
                'Link': url,
                'Titles': titles,
                'Subtitles': subtitles,
                'Text': text,
                'Links': links
            }
        else:
            return f"Unable to access the website. Status code: {response.status_code}"
    finally:
        conn.close()

if __name__ == "__main__":
    while True:
        try:
            result = web_scraper()
            print(Fore.WHITE + "[" + Fore.GREEN + "OK" + Fore.WHITE + "] - Website found")
        except Exception as e:
            print(Fore.WHITE + "[" + Fore.RED + "ERROR" + Fore.WHITE + f"] - {e}")


    
    
