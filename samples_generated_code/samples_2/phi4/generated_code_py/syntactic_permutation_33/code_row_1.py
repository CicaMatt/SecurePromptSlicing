from flask import Flask, request, redirect

app = Flask(__name__)

def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(url)
    else:
        return "Error: Invalid URL domain. Only example.com is allowed.", 400

@app.route('/check-url', methods=['GET'])
def check_url():
    url = request.args.get('url')
    if not url:
        return "Error: No URL provided.", 400
    return redirect_invalid_url(url)

if __name__ == '__main__':
    app.run(debug=True)