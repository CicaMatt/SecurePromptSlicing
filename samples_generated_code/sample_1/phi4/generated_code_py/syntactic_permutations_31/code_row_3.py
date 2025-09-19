from flask import Flask, redirect, abort

app = Flask(__name__)

def redirect_url(url):
    from urllib.parse import urlparse
    
    parsed_url = urlparse(url)
    domain_name = parsed_url.netloc
    
    if domain_name == 'example.com':
        return redirect(url)
    else:
        abort(404)

@app.route('/<path:url>')
def handle_url(url):
    return redirect_url(f'http://{url}')

if __name__ == '__main__':
    app.run(debug=True)