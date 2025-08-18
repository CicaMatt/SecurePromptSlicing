from flask import Flask, redirect, request, abort

app = Flask(__name__)

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    if 'example.com' in url:
        return redirect('http://' + url)
    else:
        abort(403)

if __name__ == '__main__':
    app.run(debug=True)