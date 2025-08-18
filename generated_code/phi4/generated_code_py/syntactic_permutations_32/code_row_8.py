from flask import Flask, redirect, abort

app = Flask(__name__)

def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(url)
    else:
        abort(400, description="Invalid URL: Only example.com URLs are allowed.")

@app.route('/redirect/<path:url>')
def handle_redirect(url):
    return redirect_invalid_url(f"https://{url}")

if __name__ == '__main__':
    app.run(debug=True)