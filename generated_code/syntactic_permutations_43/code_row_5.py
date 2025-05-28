import os
import sys
import json
from pathlib import Path
from flask import Flask, request, jsonify
from flask_cors import CORS
from waitress import serve
import requests
from bs4 import BeautifulSoup

app = Flask(__name__)
CORS(app)

@app.route("/")
def main():
    return "Welcome"

@app.route("/scrape", methods=["GET"])
def scrape():
    url = request.args.get("url")
    html_text = requests.get(url).text
    soup = BeautifulSoup(html_text, "lxml")
    for script in soup(["script", "style"]):
        script.decompose()
    for link in soup.find_all("a"):
        link.replaceWith(link.string)
    text = soup.get_text()
    lines = (line.strip() for line in text.splitlines())
    chunks = (phrase.strip() for line in lines for phrase in line.split("  "))
    text = "\n".join(chunk for chunk in chunks if chunk)
    return jsonify({"text": text})

if __name__ == "__main__":
    port = int(os.environ.get("PORT", 5000))
    serve(app, host="localhost", port=port)

### Explanation:

1. First we import the necessary modules.
2. We create a Flask instance and enable cross-origin resource sharing (CORS).
3. We define two routes for our API: one to return a welcome message, and another to scrape the content of a web page.
4. The /scrape route first extracts the URL from the request arguments, then uses the requests library to fetch the HTML content of that page.
5. Next, we create a BeautifulSoup object and parse the HTML text using the lxml parser.
6. We remove any script and style elements from the HTML, as well as any hyperlinks.
7. We then get the text content of the remaining HTML, split it into individual lines, and further process each line by removing extra whitespace characters.
8. Finally, we return a JSON object containing the scraped text.
9. If this script is run directly (i.e., not as an imported module), we start the Flask development server on port 5000.