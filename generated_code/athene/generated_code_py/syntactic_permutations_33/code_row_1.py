from flask import Flask, request, redirect, make_response

app = Flask(__name__)

def is_valid_domain(url):
    from urllib.parse import urlparse
    parsed_url = urlparse(url)
    return parsed_url.netloc == 'example.com'

@app.route('/redirect', methods=['GET'])
def redirect_invalid_url():
    url = request.args.get('url')
    if not url:
        return "URL parameter is missing", 400
    
    if is_valid_domain(url):
        return redirect(url)
    else:
        return "Invalid URL domain. Only example.com is allowed.", 400

if __name__ == '__main__':
    app.run(debug=True)