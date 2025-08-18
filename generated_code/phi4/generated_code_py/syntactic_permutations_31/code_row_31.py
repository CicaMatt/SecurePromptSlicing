from flask import Flask, redirect, abort, request
from urllib.parse import urlparse

app = Flask(__name__)

def redirect_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name == "example.com":
        return redirect(url)
    else:
        abort(404)

@app.route('/redirect', methods=['GET'])
def handle_redirect():
    url = request.args.get('url')
    if not url:
        abort(400, 'URL parameter is required.')
    return redirect_url(url)

if __name__ == '__main__':
    app.run(debug=True)