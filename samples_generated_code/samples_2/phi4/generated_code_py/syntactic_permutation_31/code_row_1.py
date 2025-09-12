from urllib.parse import urlparse
from flask import Flask, redirect, abort

app = Flask(__name__)

@app.route('/redirect/<path:url>')
def redirect_url(url):
    parsed_url = urlparse(url)
    if parsed_url.netloc == 'example.com':
        return redirect(url)
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)