from flask import Flask, redirect, abort

app = Flask(__name__)

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    if url.startswith('example.com'):
        return redirect(f'http://{url}', code=302)
    else:
        return "Error: URL must be from example.com", 400

if __name__ == '__main__':
    app.run(debug=True)