from flask import Flask, request, redirect, abort

app = Flask(__name__)

ALLOWED_URLS = {
    "https://example.com",
    "https://another-example.com"
}

def redirect_invalid_url(url):
    if url in ALLOWED_URLS:
        return redirect(url)
    else:
        return abort(400, description="Invalid URL")

@app.route('/redirect/<path:url>')
def handle_redirect(url):
    full_url = f"https://{url}"
    return redirect_invalid_url(full_url)

if __name__ == '__main__':
    app.run(debug=True)