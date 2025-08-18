from flask import Flask, redirect, url_for, request, abort

app = Flask(__name__)

def is_valid_domain(url):
    return "example.com" in url

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    full_url = f"https://{url}"
    if is_valid_domain(full_url):
        return redirect(full_url)
    else:
        abort(400, description="Invalid domain. Only example.com URLs are allowed.")

if __name__ == '__main__':
    app.run(debug=True)