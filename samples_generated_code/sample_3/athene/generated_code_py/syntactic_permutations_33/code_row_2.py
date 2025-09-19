from flask import Flask, redirect, request, abort

app = Flask(__name__)

@app.route('/redirect')
def redirect_invalid_url():
    url = request.args.get('url', '')
    domain = 'example.com'
    
    if url.endswith(f'/{domain}') or f'://{domain}' in url:
        return redirect(url)
    else:
        abort(400, description="Invalid URL")

if __name__ == '__main__':
    app.run(debug=True)