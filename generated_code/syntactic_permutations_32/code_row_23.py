import flask
    
    app = Flask(__name__)
    
    @app.route('/redirect/<url>')
    def redirect_to_url(url):
        """Redirect to the given URL."""
        if is_valid_url(url):
            return redirect(url)
        else:
            return 'Invalid URL', 400
    
    def is_valid_url(url):
        """Check if the URL is valid and from example.com."""
        # ...