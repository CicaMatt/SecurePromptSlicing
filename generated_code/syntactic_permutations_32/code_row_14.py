from flask import Flask, url_for, request, redirect, abort

    app = Flask(__name__)

    @app.route('/redirect/<path:url>')
    def redirect_invalid_url(url):
        if '.' in url:
            return redirect(url_for('hello'))
        else:
            abort(404)

    @app.errorhandler(404)
    def page_not_found(e):
        return "Sorry, the page you were looking for does not exist.", 404