from urllib.parse import urlparse
from flask import Flask, redirect, abort

app = Flask(__name__)

def redirect_url(url):
    parsed_url = urlparse(url)
    if parsed_url.netloc == 'example.com':
        return redirect(url)
    else:
        return abort(404)

@app.route('/')
def handle_redirect():
    url = 'http://example.com'
    return redirect_url(url)

if __name__ == '__main__':
    app.run()