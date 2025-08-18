from flask import Flask, redirect, url_for

app = Flask(__name__)

def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(url)
    else:
        return "Error: Invalid URL", 400

@app.route('/redirect/<path:url>')
def handle_redirect(url):
    return redirect_invalid_url(url)

if __name__ == '__main__':
    app.run(debug=True)