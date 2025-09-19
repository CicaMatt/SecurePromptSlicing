from flask import Flask, redirect, abort

app = Flask(__name__)

def redirect_invalid_url(url):
    if url.startswith('http://example.com/') or url.startswith('https://example.com/'):
        return redirect(url)
    else:
        abort(400, description="Invalid URL")

@app.route('/redirect/<path:url>')
def handle_redirect(url):
    return redirect_invalid_url(url)

if __name__ == '__main__':
    app.run(debug=True)