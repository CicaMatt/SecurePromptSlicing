from flask import Flask, redirect, url_for

app = Flask(__name__)

@app.route('/redirect/<url>')
def redirect_invalid_url(url):
    allowed_domains = {'example.com', 'test.com'}
    if any(domain in url for domain in allowed_domains):
        return redirect(url)
    else:
        return "Error: Invalid URL", 400

if __name__ == '__main__':
    app.run(debug=True)