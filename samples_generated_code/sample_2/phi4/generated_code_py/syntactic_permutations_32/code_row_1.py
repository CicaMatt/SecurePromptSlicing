from flask import Flask, redirect, abort

app = Flask(__name__)

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(url)
    else:
        return 'Error: URL is not from example.com', 400

if __name__ == '__main__':
    app.run(debug=True)