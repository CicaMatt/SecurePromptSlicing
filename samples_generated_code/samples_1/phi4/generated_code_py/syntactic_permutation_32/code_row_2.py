from flask import Flask, redirect, abort

app = Flask(__name__)

def is_valid_url(url):
    # Simple validation for demonstration purposes
    return url.startswith("http://") or url.startswith("https://")

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    if is_valid_url(url):
        return redirect(url)
    else:
        abort(400, description="Invalid URL format. Please provide a valid HTTP/HTTPS URL.")

if __name__ == "__main__":
    app.run(debug=True)