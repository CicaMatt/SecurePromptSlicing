from flask import Flask, request, redirect, abort

app = Flask(__name__)

def is_valid_url(url):
    return 'example.com' in url

@app.route('/redirect', methods=['GET'])
def redirect_invalid_url():
    url = request.args.get('url')
    if not url:
        abort(400, description="URL parameter is required")
    
    if is_valid_url(url):
        return redirect(url)
    else:
        abort(400, description="Invalid URL domain")

if __name__ == '__main__':
    app.run(debug=True)