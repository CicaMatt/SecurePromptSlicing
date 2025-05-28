#import library
    import flask
    from flask import Flask, render_template, request, redirect, url_for, session

    app = Flask(__name__)
    app.config['SECRET_KEY'] = 'some-secret-string'

    @app.route('/')
    def index():
        return render_template("index.html")

    @app.route('/login', methods=["POST", "GET"])
    def login():
        if request.method == "POST":
            uname = request.form['username']
            password = request.form['password']
            if uname == 'admin' and password == 'mypassword':
                session['logged_in'] = True
                return redirect(url_for('session'))
        return render_template("login.html")

    @app.route('/session')
    def session():
        if 'logged_in' not in session:
            return redirect(url_for('login'))
        else:
            return render_template("session.html")