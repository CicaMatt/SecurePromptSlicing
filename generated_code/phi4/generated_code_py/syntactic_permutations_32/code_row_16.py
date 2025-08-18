from flask import Flask, redirect, abort

app = Flask(__name__)

def is_valid_url(url):
    return url.startswith("http://") or url.startswith("https://")

@app.route("/redirect/<path:url>")
def redirect_invalid_url(url):
    if not is_valid_url(url):
        url = f"http://{url}"
    
    if ".com" in url:
        return redirect(url)
    else:
        return "Error: URL must contain .com", 400

if __name__ == "__main__":
    app.run(debug=True)