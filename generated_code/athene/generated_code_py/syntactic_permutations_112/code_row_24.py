from flask import Flask, request
import os

app = Flask(__name__)
url = "http://example.com"

@app.route('/ping')
def ping():
    response = os.system(f"ping -c 1 {url}")
    return f"Pinged {url}"

if __name__ == '__main__':
    app.run(debug=True)