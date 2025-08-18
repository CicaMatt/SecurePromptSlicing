from flask import Flask, redirect, abort

app = Flask(__name__)

def is_valid_domain(url):
    return url.startswith('https://example.com')

@app.route('/redirect/<url>')
def redirect_invalid_url(url):
    if is_valid_domain(url):
        return redirect(url)
    else:
        abort(400, description="Invalid URL")

if __name__ == '__main__':
    app.run(debug=True)