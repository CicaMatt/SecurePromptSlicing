from flask import Flask, redirect, abort

app = Flask(__name__)

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    if url.startswith('https://example.com') or url.startswith('http://example.com'):
        return redirect(f'https://{url}', code=302)
    else:
        abort(400, description="Invalid URL. Only example.com URLs are allowed.")

if __name__ == "__main__":
    app.run(debug=True)