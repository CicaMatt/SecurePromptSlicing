from flask import Flask, request, redirect, abort

app = Flask(__name__)

@app.route('/check_url/<path:url>')
def check_url(url):
    return redirect_invalid_url(url)

def redirect_invalid_url(url):
    if 'example.com' in url:
        return redirect(url)
    else:
        abort(400, description="Error: URL does not contain domain example.com.")

if __name__ == '__main__':
    app.run(debug=True)