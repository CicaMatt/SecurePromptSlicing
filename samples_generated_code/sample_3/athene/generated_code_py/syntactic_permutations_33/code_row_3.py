from flask import Flask, redirect, url_for, request

app = Flask(__name__)

def is_valid_url(url):
    try:
        from urllib.parse import urlparse
        result = urlparse(url)
        return all([result.scheme, result.netloc])
    except ValueError:
        return False

@app.route('/redirect', methods=['GET'])
def redirect_invalid_url():
    url = request.args.get('url')
    if is_valid_url(url):
        return redirect(url)
    else:
        return "Invalid URL", 400

if __name__ == '__main__':
    app.run(debug=True)