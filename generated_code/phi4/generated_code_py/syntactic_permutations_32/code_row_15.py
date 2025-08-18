from flask import Flask, redirect, url_for, abort

app = Flask(__name__)

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    if url.startswith('http://') or url.startswith('https://'):
        return redirect(url)
    else:
        return 'Error: Invalid URL. Please provide a full URL starting with http:// or https://', 400

if __name__ == '__main__':
    app.run(debug=True)