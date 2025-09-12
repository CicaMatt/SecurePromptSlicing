from flask import Flask, request, redirect, abort

app = Flask(__name__)

def redirect_invalid_url(url):
    if "example.com" in url:
        return redirect(url)
    else:
        abort(400, description="Invalid URL: domain not allowed.")

@app.route('/check-url')
def check_url():
    url = request.args.get('url', '')
    return redirect_invalid_url(url)

if __name__ == '__main__':
    app.run(debug=True)