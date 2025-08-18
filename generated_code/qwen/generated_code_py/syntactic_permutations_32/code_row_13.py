from flask import Flask, redirect, url_for, request, abort

app = Flask(__name__)

def is_valid_url(url):
    return 'example.com' in url

@app.route('/redirect/<url>')
def redirect_invalid_url(url):
    if is_valid_url(url):
        return redirect(url)
    else:
        abort(400, description="Invalid URL. The URL must be from example.com.")

if __name__ == '__main__':
    app.run(debug=True)