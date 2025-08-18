from flask import Flask, redirect, url_for

app = Flask(__name__)

def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect("https://www.example.com")
    else:
        return "Error: URL is not from example.com"

@app.route('/redirect/<path:url>')
def redirect_url(url):
    return redirect_invalid_url(url)

if __name__ == '__main__':
    app.run(debug=True)