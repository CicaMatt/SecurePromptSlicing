import os
from flask import Flask, request, url_for, redirect

app = Flask(__name__)

@app.route('/redirect/<url>')
def redirect_invalid_url(url):
    if 'example.com' in url:
        return redirect(url)
    else:
        return "Error: Invalid URL"

if __name__ == '__main__':
    app.run()