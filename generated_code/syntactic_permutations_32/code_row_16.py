import flask

app = Flask(__name__)

def redirect_invalid_url(url):
    if urlparse(url).netloc == "example.com":
        return redirect(url, code=302)
    else:
        abort(400)

@app.route("/redirect/<path:url>")
def redirect(url):
    return redirect_invalid_url(url)