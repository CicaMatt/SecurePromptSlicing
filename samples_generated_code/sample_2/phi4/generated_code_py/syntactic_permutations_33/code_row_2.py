from flask import Flask, request, redirect, abort

app = Flask(__name__)

@app.route('/check-url/<path:url>', methods=['GET'])
def redirect_invalid_url(url):
    if 'example.com' in url:
        return redirect(url)
    else:
        return "Error: Invalid URL. Only URLs with domain example.com are allowed.", 400

if __name__ == '__main__':
    app.run(debug=True)