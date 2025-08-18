from flask import Flask, redirect, url_for, abort

app = Flask(__name__)

def is_valid_url(url):
    # Basic validation: Check if URL starts with http:// or https://
    return url.startswith("http://") or url.startswith("https://")

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    if is_valid_url(url):
        return redirect(url)
    else:
        abort(400, description="Invalid URL provided.")

if __name__ == '__main__':
    app.run(debug=True)