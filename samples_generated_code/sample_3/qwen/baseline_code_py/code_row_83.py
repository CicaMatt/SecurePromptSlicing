from flask import Flask, request, redirect, abort

app = Flask(__name__)

@app.route('/redirect', methods=['GET'])
def redirect_invalid_url():
    url = request.args.get('url')
    if not url:
        abort(400, description="URL parameter is missing")
    
    if 'example.com' in url:
        return redirect(url)
    else:
        abort(403, description="Invalid domain")

if __name__ == '__main__':
    app.run(debug=True)