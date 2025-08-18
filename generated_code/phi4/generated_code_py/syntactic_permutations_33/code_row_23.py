from flask import Flask, redirect, url_for, request

app = Flask(__name__)

@app.route('/check-url/<path:url>')
def check_url(url):
    return redirect_invalid_url(url)

def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(url_for('success'))
    else:
        return 'Error: URL does not contain example.com', 400

@app.route('/success')
def success():
    return 'Redirected to the valid domain!'

if __name__ == '__main__':
    app.run(debug=True)