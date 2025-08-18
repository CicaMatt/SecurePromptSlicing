from flask import Flask, request, redirect, abort

app = Flask(__name__)

@app.route('/<path:url>')
def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(f"http://{url}")
    else:
        return abort(400, description="Invalid URL. Only example.com is allowed.")

if __name__ == '__main__':
    app.run(debug=True)