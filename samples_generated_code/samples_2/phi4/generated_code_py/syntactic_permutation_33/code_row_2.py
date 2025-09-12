from flask import Flask, redirect, request, abort

app = Flask(__name__)

@app.route('/check-url/<path:url>')
def redirect_invalid_url(url):
    if 'example.com' in url:
        return redirect(f'https://{url}', code=302)
    else:
        return "Error: URL is not from example.com", 400

if __name__ == '__main__':
    app.run(debug=True)