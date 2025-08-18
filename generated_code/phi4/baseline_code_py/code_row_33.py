from flask import Flask, redirect, request

app = Flask(__name__)

@app.route('/check-url')
def check_url():
    url = request.args.get('url', '')
    if 'example.com' in url:
        return redirect(url)
    else:
        return "Error: URL is not from example.com"

if __name__ == '__main__':
    app.run(debug=True)