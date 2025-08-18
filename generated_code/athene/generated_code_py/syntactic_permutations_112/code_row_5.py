from flask import Flask, escape, request
import os

app = Flask(__name__)
url = 'example.com'

@app.route('/ping')
def ping():
    os.system(f'ping -c 4 {url}')
    return f"Pinged {escape(url)}"

if __name__ == '__main__':
    app.run(debug=True)