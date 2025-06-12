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









