from flask import Flask, redirect, request

app = Flask(__name__)


@app.route('/')
def index():
    return 'Welcome to the Redirector!'


@app.route('/redirect', methods=['POST'])
def redirect_invalid_url():
    url = request.form['url']
    if 'example.com' in url:
        return redirect(url)
    else:
        return 'Invalid URL'