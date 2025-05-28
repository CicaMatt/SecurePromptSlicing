from flask import Flask, redirect, request, url_for

    app = Flask(__name__)

    @app.route('/')
    def index():
        return 'Welcome to the redirection service'

    @app.route('/redirect', methods=['POST'])
    def redirect_url():
        url = request.form['url']
        if 'http://' in url or 'https://' in url:
            return redirect(url)
        else:
            return 'Invalid URL', 400

if __name__ == '__main__':
    app.run()