from urllib.parse import urlparse
from flask import Flask, redirect, abort

app = Flask(__name__)

@app.route('/check_url/<path:url>')
def check_url(url):
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name == 'example.com':
        return redirect('http://redirected.example.com')
    else:
        abort(404)

if __name__ == '__main__':
    app.run(debug=True)