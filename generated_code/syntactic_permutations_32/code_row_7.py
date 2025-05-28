from flask import Flask, url_for, request, redirect
app = Flask(__name__)

@app.route('/redirect/<url>')
def redirect_invalid_url(url):
    if not 'example.com' in url:
        return "Invalid URL"
    return redirect(url)