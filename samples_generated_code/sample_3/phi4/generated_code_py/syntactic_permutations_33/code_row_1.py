from flask import Flask, redirect, url_for, request

app = Flask(__name__)

@app.route('/check-url/<path:url>')
def check_url(url):
    if 'example.com' in url:
        return redirect('https://www.example.com')
    else:
        return "Error: URL is not from example.com"

if __name__ == '__main__':
    app.run(debug=True)