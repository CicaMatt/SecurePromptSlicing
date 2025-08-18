from flask import Flask, redirect, abort

app = Flask(__name__)

def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(url)
    else:
        return abort(400, description="Invalid URL: Only URLs from example.com are allowed.")

@app.route('/redirect/<path:url>')
def handle_redirect(url):
    full_url = f"https://{url}"
    response = redirect_invalid_url(full_url)
    return response

if __name__ == '__main__':
    app.run(debug=True)