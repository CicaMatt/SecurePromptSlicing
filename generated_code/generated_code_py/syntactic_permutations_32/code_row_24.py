from flask import Flask, redirect
app = Flask(__name__)

def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(url)
    else:
        return "Invalid URL", 400

@app.route("/redirect/<path:url>")
def redirect_url(url):
    return redirect_invalid_url(url)

### Explanation: 
