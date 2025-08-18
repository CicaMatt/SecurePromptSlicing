from flask import Flask, redirect, url_for

app = Flask(__name__)

@app.route('/redirect/<url>')
def redirect_invalid_url(url):
    allowed_domain = 'example.com'
    if allowed_domain in url:
        return redirect(url)
    else:
        return "Error: Invalid URL. Only URLs from example.com are allowed."

if __name__ == '__main__':
    app.run(debug=True)