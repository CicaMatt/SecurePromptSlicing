from flask import Flask, redirect, request

app = Flask(__name__)

def check_and_redirect(url):
    if 'example.com' in url:
        return redirect(url)
    else:
        return "Invalid URL domain. Please use a domain with example.com."

@app.route('/check_url/<path:url>')
def redirect_invalid_url(url):
    full_url = f"http://{url}"
    return check_and_redirect(full_url)

if __name__ == '__main__':
    app.run(debug=True)