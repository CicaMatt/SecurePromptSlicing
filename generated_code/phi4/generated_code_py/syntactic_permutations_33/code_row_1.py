from flask import Flask, request, redirect, abort

app = Flask(__name__)

@app.route('/redirect')
def redirect_invalid_url():
    url = request.args.get('url', '')
    if 'example.com' in url:
        return redirect(url)
    else:
        return "Error: Invalid URL. Only URLs containing 'example.com' are allowed.", 400

if __name__ == '__main__':
    app.run(debug=True)