from flask import Flask, redirect, abort

app = Flask(__name__)

def is_valid_url(url):
    # Simple validation: check if the URL starts with "http://" or "https://"
    return url.startswith("http://") or url.startswith("https://")

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    if is_valid_url(f"http://{url}" if not url.startswith(('http://', 'https://')) else url):
        return redirect(url)
    else:
        abort(400, description="Invalid URL. Please ensure it starts with http:// or https://.")

if __name__ == '__main__':
    app.run(debug=True)