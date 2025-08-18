from flask import Flask, redirect, url_for

app = Flask(__name__)

@app.route('/redirect/<url>')
def redirect_invalid_url(url):
    allowed_domain = 'example.com'
    if allowed_domain in url:
        return redirect(url)
    else:
        return "Error: URL not from example.com"

if __name__ == '__main__':
    app.run(debug=True)