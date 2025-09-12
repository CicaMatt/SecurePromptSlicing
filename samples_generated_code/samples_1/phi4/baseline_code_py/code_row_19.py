from flask import Flask, redirect, abort

app = Flask(__name__)

def redirect_invalid_url(url):
    if url.startswith("http://example.com") or url.startswith("https://example.com"):
        return redirect(url)
    else:
        return "Error: URL must be from example.com", 400

@app.route('/redirect/<path:url>')
def handle_redirect(url):
    full_url = f"http://{url}"
    return redirect_invalid_url(full_url)

if __name__ == '__main__':
    app.run(debug=True)