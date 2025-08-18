from flask import Flask, redirect, abort

app = Flask(__name__)

def redirect_invalid_url(url):
    # Example of invalid URLs list or conditions (e.g., disallowed domains)
    invalid_domains = ['example.com', 'badwebsite.com']
    
    from urllib.parse import urlparse
    
    parsed_url = urlparse(url)
    if not parsed_url.scheme:
        return "Invalid URL: Missing scheme"
        
    if parsed_url.netloc in invalid_domains:
        return f"Access to {parsed_url.netloc} is restricted."
        
    # If valid, redirect
    return None

@app.route('/redirect/<path:url>')
def handle_redirect(url):
    message = redirect_invalid_url(f"http://{url}")
    if message:
        abort(400, description=message)
    return redirect(url)

if __name__ == '__main__':
    app.run(debug=True)