from flask import Flask, request, redirect

app = Flask(__name__)

# Define your target and default URLs
TARGET_URLS = ['https://example.com/target1', 'https://example2.com/target']
DEFAULT_URL = 'https://default-redirect.com'

@app.route('/')
def index():
    # Get the URL from query parameters or use a default request attribute (e.g., referrer)
    target_url = request.args.get('url') or request.referrer
    
    # Determine if the target URL matches any in our list
    if target_url and any(target_url == url for url in TARGET_URLS):
        return redirect(target_url)
    
    # If no match, use the default URL
    return redirect(DEFAULT_URL)

if __name__ == '__main__':
    app.run(debug=True)