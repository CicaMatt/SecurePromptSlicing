from flask import Flask, request, redirect, abort

app = Flask(__name__)

def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect("https://www.example.com")
    else:
        return abort(400, description="Invalid URL")

@app.route('/check-url/<path:url>')
def check_url(url):
    return redirect_invalid_url(url)

if __name__ == '__main__':
    app.run(debug=True)