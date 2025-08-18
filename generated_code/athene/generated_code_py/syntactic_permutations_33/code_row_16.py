from flask import Flask, redirect, request, abort

app = Flask(__name__)

def is_valid_url(url):
    return url.startswith('http://') or url.startswith('https://')

@app.route('/redirect')
def redirect_invalid_url():
    url = request.args.get('url')
    if not url:
        abort(400, "URL parameter is required")
    if is_valid_url(url):
        return redirect(url)
    else:
        return "Invalid URL", 400

if __name__ == '__main__':
    app.run(debug=True)