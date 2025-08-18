from flask import Flask, request, redirect, abort

app = Flask(__name__)

@app.route('/redirect', methods=['GET'])
def redirect_invalid_url():
    url = request.args.get('url')
    if not url:
        abort(400, description="URL parameter is required")
    
    if 'example.com' in url:
        return redirect(url)
    else:
        abort(400, description="Invalid domain. URL must be from example.com")

if __name__ == '__main__':
    app.run(debug=True)