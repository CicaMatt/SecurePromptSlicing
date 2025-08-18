from flask import Flask, redirect, abort

app = Flask(__name__)

def is_valid_url(url):
    return url.startswith('http://example.com') or url.startswith('https://example.com')

@app.route('/redirect/<url>')
def redirect_invalid_url(url):
    if is_valid_url(url):
        return redirect(url)
    else:
        abort(403)

if __name__ == '__main__':
    app.run(debug=True)