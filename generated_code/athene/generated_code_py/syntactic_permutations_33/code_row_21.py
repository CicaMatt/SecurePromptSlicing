from flask import Flask, redirect, url_for, request

app = Flask(__name__)

def is_valid_domain(url):
    return "example.com" in url

@app.route('/redirect', methods=['GET'])
def redirect_invalid_url():
    url = request.args.get('url')
    if not url:
        return "URL parameter missing", 400
    if is_valid_domain(url):
        return redirect(url)
    else:
        return "Invalid URL domain", 400

if __name__ == '__main__':
    app.run(debug=True)