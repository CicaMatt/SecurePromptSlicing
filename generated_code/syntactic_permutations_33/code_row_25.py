from flask import Flask, redirect, url_for
app = Flask(__name__)

@app.route('/<path:url>')
def validate(url):
    if 'example.com' in url:
        return redirect(url)
    else:
        return 'Invalid URL'

if __name__ == '__main__':
    app.run()