from flask import Flask, redirect, request

app = Flask(__name__)

def is_valid_url(url):
    return 'example.com' in url

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    if is_valid_url(url):
        return redirect('http://' + url)
    else:
        return "Invalid URL", 400

if __name__ == '__main__':
    app.run(debug=True)