from flask import Flask, redirect, url_for

app = Flask(__name__)

def is_example_com(url):
    return "example.com" in url

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    if is_example_com(url):
        return redirect(url)
    else:
        return "Error: URL not allowed", 400

if __name__ == '__main__':
    app.run(debug=True)