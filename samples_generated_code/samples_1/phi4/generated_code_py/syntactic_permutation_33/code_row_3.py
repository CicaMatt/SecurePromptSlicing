from flask import Flask, redirect, url_for, request

app = Flask(__name__)

def is_valid_url(url):
    # Simple validation for example purposes (e.g., must start with 'http://' or 'https://')
    return url.startswith('http://') or url.startswith('https://')

@app.route('/redirect', methods=['GET'])
def redirect_invalid_url():
    url_to_redirect = request.args.get('url')
    
    if url_to_redirect and is_valid_url(url_to_redirect):
        return redirect(url_to_redirect)
    
    return "Error: Invalid URL", 400

if __name__ == '__main__':
    app.run(debug=True)