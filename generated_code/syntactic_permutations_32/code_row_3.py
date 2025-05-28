import flask
    app = flask.Flask(__name__)
    
    @app.route('/redirect/<url>')
    def redirect_invalid_url(url):
        if 'example.com' in url:
            return flask.redirect(url)
        else:
            return f'Invalid URL {url}'