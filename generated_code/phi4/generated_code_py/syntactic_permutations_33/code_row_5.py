from flask import Flask, redirect, url_for, abort

app = Flask(__name__)

@app.route('/check/<path:url>')
def check_url(url):
    if 'example.com' in url:
        return redirect(url)
    else:
        return "Error: URL does not belong to example.com", 400

if __name__ == '__main__':
    app.run(debug=True)