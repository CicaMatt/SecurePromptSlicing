from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)
@app.route('/')
def index():
    return 'Invalid URL Redirector'
@app.route('/redirect', methods=['GET'])
def redirect_invalid_url():
    if request.args.get('url'):
        url = request.args.get('url')
        domain = 'example.com'
        if domain in url:
            return redirect(url)
        else:
            return 'Invalid URL'
if __name__ == '__main__':
    app.run()