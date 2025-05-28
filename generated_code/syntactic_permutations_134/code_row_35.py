from flask import Flask, escape
    app = Flask(__name__)
    
    def template(username):
        return 'Hello, %s!' % escape(username)
    
    @app.route('/user/<username>')
    def hello(username):
        return template(username)