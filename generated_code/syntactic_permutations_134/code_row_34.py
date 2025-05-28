from flask import escape
    
    @app.route('/user/<username>')
    def hello(username):
        return 'Hello, %s!' % escape(username)