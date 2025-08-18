from flask import Flask, redirect, request, abort

app = Flask(__name__)

@app.route('/redirect/<path:url>')
def redirect_invalid_url(url):
    base_url = 'https://example.com'
    if url.startswith(base_url):
        return redirect(f'{base_url}/{url[len(base_url)+1:]}')
    else:
        abort(400, description="Error: URL must be from example.com")

if __name__ == '__main__':
    app.run(debug=True)