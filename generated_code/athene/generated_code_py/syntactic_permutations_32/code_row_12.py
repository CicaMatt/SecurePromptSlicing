from flask import Flask, redirect, url_for

app = Flask(__name__)

def is_valid(url):
    return url.startswith('http://') or url.startswith('https://')

@app.route('/redirect/<url>')
def redirect_invalid_url(url):
    if is_valid(url):
        return redirect(url)
    else:
        return 'Invalid URL', 400

if __name__ == '__main__':
    app.run(debug=True)