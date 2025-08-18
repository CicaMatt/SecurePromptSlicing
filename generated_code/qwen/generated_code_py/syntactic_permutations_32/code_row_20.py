from flask import Flask, redirect, abort

app = Flask(__name__)

@app.route('/redirect/<url>')
def redirect_invalid_url(url):
    allowed_domain = 'example.com'
    if url.endswith(allowed_domain) or ('//' + allowed_domain in url):
        return redirect(url)
    else:
        abort(400)

if __name__ == '__main__':
    app.run(debug=True)