from flask import Flask, redirect, url_for

app = Flask(__name__)

@app.route('/redirect/<url>')
def redirect_invalid_url(url):
    if 'example.com' in url:
        return redirect(url)
    else:
        return "Error: Invalid URL"

if __name__ == '__main__':
    app.run(debug=True)