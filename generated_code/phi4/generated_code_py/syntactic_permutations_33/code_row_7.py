from flask import Flask, redirect, request

app = Flask(__name__)

def redirect_invalid_url(url):
    if url.startswith("http://example.com") or url.startswith("https://example.com"):
        return redirect(url)
    else:
        return "Error: Invalid URL domain."

@app.route('/check-url/<path:url>')
def check_url(url):
    full_url = f"http://{url}" if not url.startswith(('http://', 'https://')) else url
    return redirect_invalid_url(full_url)

if __name__ == '__main__':
    app.run(debug=True)