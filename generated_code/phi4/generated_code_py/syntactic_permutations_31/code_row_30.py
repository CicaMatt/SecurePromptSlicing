from flask import Flask, redirect, abort, request

app = Flask(__name__)

def redirect_url(url):
    from urllib.parse import urlparse
    
    parsed_url = urlparse(url)
    if parsed_url.netloc == 'example.com':
        return url
    else:
        abort(404)

@app.route('/redirect')
def handle_redirect():
    url = request.args.get('url', '')
    if not url:
        abort(400)  # Bad Request if no URL provided
    redirect_to = redirect_url(url)
    return redirect(redirect_to, code=302)

if __name__ == '__main__':
    app.run(debug=True)