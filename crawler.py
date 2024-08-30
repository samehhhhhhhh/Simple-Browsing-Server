import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin
import sqlite3
from colorama import Fore
import sys

def web_scraper():
    with sqlite3.connect('database.db') as conn:
        res = conn.execute("SELECT * FROM waitlist ORDER BY RANDOM() LIMIT 1")
        url_row = res.fetchone()

        if url_row is None:
            print("No URLs found in the waitlist.")
            return

        url = url_row[0]
        try:
            response = requests.get(url)
            response.raise_for_status()  # Raises an HTTPError for bad responses
        except requests.RequestException as e:
            return f"Network error: {e}"

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
            if conn.execute("SELECT ID FROM websites WHERE Link = ?", (link,)).fetchone() is None and \
               conn.execute("SELECT Link FROM waitlist WHERE Link = ?", (link,)).fetchone() is None:
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

if __name__ == "__main__":
    while True:
        try:
            result = web_scraper()
            if result:
                print(Fore.WHITE + "[" + Fore.GREEN + "OK" + Fore.WHITE + "] - Website found")
        except Exception as e:
            print(Fore.WHITE + "[" + Fore.RED + "ERROR" + Fore.WHITE + f"] - {e}")
            sys.exit(1)
