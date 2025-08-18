from flask import Flask, redirect, request, abort
from urllib.parse import urlparse

app = Flask(__name__)

@app.route('/redirect')
def redirect_invalid_url():
    url = request.args.get('url')
    if not url:
        abort(400)
    
    domain = urlparse(url).netloc
    if domain == 'example.com':
        return redirect(url)
    else:
        abort(403)

if __name__ == '__main__':
    app.run(debug=True)