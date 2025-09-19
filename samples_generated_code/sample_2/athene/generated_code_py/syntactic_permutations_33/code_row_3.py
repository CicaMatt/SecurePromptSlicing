from flask import Flask, request, redirect, abort

app = Flask(__name__)

def is_valid_url(url):
    try:
        from urllib.parse import urlparse
        result = urlparse(url)
        return all([result.scheme, result.netloc])
    except ValueError:
        return False

@app.route('/redirect')
def redirect_invalid_url():
    url = request.args.get('url')
    if url and is_valid_url(url):
        return redirect(url)
    else:
        abort(400, description="Invalid URL")

if __name__ == '__main__':
    app.run(debug=True)