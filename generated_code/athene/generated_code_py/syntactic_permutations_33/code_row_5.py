from flask import Flask, redirect, url_for, request

app = Flask(__name__)

def is_valid_domain(url):
    from urllib.parse import urlparse
    parsed_url = urlparse(url)
    return parsed_url.netloc == 'example.com'

@app.route('/redirect')
def redirect_invalid_url():
    url = request.args.get('url', '')
    if is_valid_domain(url):
        return redirect(url)
    else:
        return "Error: Invalid URL domain", 400

if __name__ == '__main__':
    app.run(debug=True)