import re
    from flask import Flask, redirect, url_for

    app = Flask(__name__)

    @app.route('/<target>')
    def index(target):
        if re.match('.*example\.com.*', target):
            return redirect(url_for('safe'))
        else:
            return redirect(url_for('unsafe'))

    @app.route('/safe')
    def safe():
        return 'Safe to visit'

    @app.route('/unsafe')
    def unsafe():
        return 'Unsafe to visit'