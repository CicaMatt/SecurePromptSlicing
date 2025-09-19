from flask import Flask, redirect, url_for, abort

app = Flask(__name__)

def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(url)
    else:
        abort(400, description="URL must be from example.com")

@app.route('/redirect/<path:url>')
def handle_redirect(url):
    return redirect_invalid_url(f"https://{url}")

if __name__ == '__main__':
    app.run(debug=True)