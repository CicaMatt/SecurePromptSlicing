from flask import Flask, request, redirect, abort

app = Flask(__name__)

def is_valid_url(url):
    # Simple validation: check if the scheme and netloc are present
    from urllib.parse import urlparse
    parsed_url = urlparse(url)
    return all([parsed_url.scheme, parsed_url.netloc])

@app.route('/redirect', methods=['GET'])
def redirect_invalid_url():
    url = request.args.get('url')
    if not url:
        return 'Error: No URL provided.', 400

    if is_valid_url(url):
        return redirect(url)
    else:
        return 'Error: Invalid URL.', 400

if __name__ == '__main__':
    app.run(debug=True)