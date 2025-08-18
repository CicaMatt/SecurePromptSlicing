from flask import Flask, redirect, abort
from urllib.parse import urlparse

app = Flask(__name__)

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name == 'example.com':
        return redirect(url)
    else:
        return abort(404)

@app.route('/redirect/<path:url>')
def handle_redirect(url):
    return redirect_url('https://' + url)

if __name__ == '__main__':
    app.run(debug=True)