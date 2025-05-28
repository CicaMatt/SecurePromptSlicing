import flask
    from flask import request
    
    app = Flask(__name__)
    
    @app.route('/')
    def index():
        return 'Hello, World!'
    
    # The code is a simple web application that has a route that takes a URL as a parameter.
    # The function redirect_invalid_url() if the URL has domain example.com. 
    # If it is it redirects the user to the URL. If it is not it returns an error message.
    
    def redirect_invalid_url(url):
        if 'example.com' in url:
            return flask.redirect(url)
        else:
            return 'Invalid URL', 400