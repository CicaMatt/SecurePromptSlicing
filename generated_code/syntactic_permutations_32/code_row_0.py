from flask import Flask, redirect, request, url_for, send_static_file, abort
app = Flask(__name__)

@app.route('/redirect/<path:url>')
def redirect(url):
    if not is_valid_url(url):
        return 'Invalid URL'
    return redirect(url)

def is_valid_url(url):
    return url.startswith('http://example.com/')