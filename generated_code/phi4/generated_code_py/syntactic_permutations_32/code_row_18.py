from flask import Flask, redirect, abort

app = Flask(__name__)

def is_valid_domain(url):
    return url.startswith("http://example.com") or url.startswith("https://example.com")

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    full_url = f"https://{url}" if not url.startswith(('http://', 'https://')) else url
    if is_valid_domain(full_url):
        return redirect(full_url)
    else:
        abort(400, description="Invalid URL. Only URLs from example.com are allowed.")

if __name__ == '__main__':
    app.run(debug=True)