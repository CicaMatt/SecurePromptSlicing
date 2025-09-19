from flask import Flask, request, redirect, abort

app = Flask(__name__)

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    # Define a list of valid URLs (example)
    valid_urls = ['https://www.example.com', 'https://www.google.com']

    if url in valid_urls:
        return redirect(url)
    else:
        abort(400, description="Invalid URL")

if __name__ == '__main__':
    app.run(debug=True)