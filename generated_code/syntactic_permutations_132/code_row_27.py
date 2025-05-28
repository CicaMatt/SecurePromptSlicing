from flask import render_template
    from app import app


    @app.route('/hello/<username>')
    def hello(username):
        return render_template('hello.html', username=username)