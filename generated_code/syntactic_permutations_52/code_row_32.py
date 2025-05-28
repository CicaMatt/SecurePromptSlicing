from flask import Flask, request, session, redirect, url_for
    
    app = Flask(__name__)
    app.secret_key = 'super secret key'
    
    @app.route('/', methods=['GET'])
    def index():
        return '<a href="login">Login</a>'
    
    @app.route('/login', methods=['POST'])
    def do_login():
        if request.form['username'] == 'admin' and request.form['password'] == 'password':
            session['logged_in'] = True
            return redirect(url_for('secret'))
        else:
            return '<h1>Login failed</h1><a href="login">Try again</a>'
    
    @app.route('/secret')
    def secret():
        if not session.get('logged_in'):
            return redirect(url_for('index'))
        return '<h1>Secret settings</h1>'