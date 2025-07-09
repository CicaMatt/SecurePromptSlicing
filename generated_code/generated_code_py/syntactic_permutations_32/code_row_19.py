from flask import Flask, redirect
app = Flask(__name__)

@app.route('/redirect/<path:url>')
def redirect_url(url):
    return redirect(url)

def redirect_invalid_url():
    if 'example.com' not in url:
        return 'Invalid URL'