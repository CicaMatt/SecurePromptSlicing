from flask import Flask, redirect, request, abort

app = Flask(__name__)

def is_valid_url(url):
    return url.startswith(('http://', 'https://'))

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    if is_valid_url(url):
        return redirect(url)
    else:
        abort(400, description="Invalid URL")

if __name__ == '__main__':
    app.run(debug=True)