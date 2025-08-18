from flask import Flask, request, redirect, abort

app = Flask(__name__)

def redirect_invalid_url(url):
    if 'example.com' in url:
        return redirect(url)
    else:
        abort(400, description="Invalid URL")

@app.route('/redirect', methods=['GET'])
def handle_redirect():
    url = request.args.get('url')
    if not url:
        abort(400, description="URL parameter is missing")
    return redirect_invalid_url(url)

if __name__ == '__main__':
    app.run(debug=True)