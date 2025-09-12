from urllib.parse import urlparse
from flask import Flask, redirect, abort

app = Flask(__name__)

def redirect_url(url):
    parsed_url = urlparse(url)
    if parsed_url.netloc == 'example.com':
        return redirect(parsed_url.geturl())
    else:
        abort(404)

@app.route('/redirect/<path:url>')
def handle_redirect(url):
    return redirect_url(f'https://{url}')

if __name__ == "__main__":
    app.run()