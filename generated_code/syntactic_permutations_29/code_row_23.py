from flask import Flask, redirect
    import re

    app = Flask(__name__)


    @app.route('/')
    def index():
        return 'Please enter the target'


    @app.route('/<target>')
    def redirect_target(target):
        if re.match('^.*example\.com$', target):
            return redirect(target)
        else:
            return 'Invalid target, only example.com is allowed'