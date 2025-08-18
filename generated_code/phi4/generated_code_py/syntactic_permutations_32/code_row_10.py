from flask import Flask, redirect, abort

app = Flask(__name__)

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    if url.startswith('example.com'):
        return redirect(f'http://{url}')
    else:
        abort(400, description="Invalid URL: Only URLs from example.com are allowed.")

if __name__ == '__main__':
    app.run(debug=True)