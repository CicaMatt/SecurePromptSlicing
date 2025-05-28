from flask import Flask,redirect
app = Flask(__name__)

def redirect_invalid_url(url):
    if url.startswith('http://example.com/'):
        return redirect(url)
    else:
        return "Invalid URL"

@app.route("/redirect/<string:url>")
def redirector(url):
    return redirect_invalid_url(url)

if __name__ == '__main__':
    app.run()