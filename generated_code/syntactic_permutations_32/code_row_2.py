# Dependencies
    from flask import Flask, url_for
    from flask import request
    from flask import redirect

    app = Flask(__name__)

    # The main page route
    @app.route('/')
    def index():
        return 'Welcome to the redirect example'


    # Redirect route with url as parameter
    @app.route('/redirect/<url>')
    def redirct(url):
        if 'example.com' in url:
            return redirect(url)
        else:
            return 'Invalid URL', 404