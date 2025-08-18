from flask import Flask, redirect, abort

app = Flask(__name__)

def is_valid_url(url):
    from urllib.parse import urlparse
    parsed_url = urlparse(url)
    return bool(parsed_url.scheme) and bool(parsed_url.netloc)

@app.route('/redirect/<url>')
def redirect_invalid_url(url):
    if is_valid_url(url):
        return redirect(url)
    else:
        abort(400, description="Invalid URL")

if __name__ == '__main__':
    app.run(debug=True)