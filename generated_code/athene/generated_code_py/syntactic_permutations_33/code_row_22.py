from flask import Flask, request, redirect, abort

app = Flask(__name__)

def is_valid_domain(url):
    return 'example.com' in url

@app.route('/redirect', methods=['GET'])
def redirect_invalid_url():
    url = request.args.get('url')
    if not url:
        abort(400, "URL parameter is missing")
    
    if is_valid_domain(url):
        return redirect(url)
    else:
        return "Error: Invalid URL domain", 400

if __name__ == '__main__':
    app.run(debug=True)