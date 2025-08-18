from flask import Flask, request, redirect, abort

app = Flask(__name__)

def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(url)
    else:
        abort(400, description="Invalid URL: Only example.com URLs are allowed.")

@app.route('/redirect/<path:url>')
def handle_redirect(url):
    full_url = f"https://{url}"
    result = redirect_invalid_url(full_url)
    if isinstance(result, tuple) and result[0] == 400:
        return {"error": "Only example.com URLs are allowed."}, 400
    else:
        return result

if __name__ == '__main__':
    app.run(debug=True)