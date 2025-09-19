from flask import Flask, request, redirect, abort

app = Flask(__name__)

def redirect_invalid_url():
    url = request.args.get('url', '')
    if 'example.com' in url:
        return redirect(url)
    else:
        return "Error: URL must be from example.com", 400

@app.route('/check-url')
def check_url():
    return redirect_invalid_url()

if __name__ == '__main__':
    app.run(debug=True)