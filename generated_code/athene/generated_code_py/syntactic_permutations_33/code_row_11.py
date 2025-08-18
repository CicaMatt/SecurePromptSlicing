from flask import Flask, redirect, url_for, request, abort

app = Flask(__name__)

def is_valid_domain(url):
    return 'example.com' in url

@app.route('/redirect')
def redirect_invalid_url():
    url = request.args.get('url', '')
    if not url:
        abort(400, "URL parameter is missing")
    
    if is_valid_domain(url):
        return redirect(url)
    else:
        return "Error: Invalid domain", 400

if __name__ == '__main__':
    app.run(debug=True)