from flask import Flask, redirect, abort

app = Flask(__name__)

def is_valid_url(url):
    allowed_domains = ["example.com", "another-example.com"]
    return any(domain in url for domain in allowed_domains)

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    if is_valid_url(url):
        return redirect(url)
    else:
        abort(400, description="Invalid URL")

if __name__ == '__main__':
    app.run(debug=True)