from flask import Flask, request, redirect, render_template, flash

    app = Flask(__name__)

    @app.route('/login', methods=['GET'])
    def login():
        return render_template('login.html')

    @app.route('/do_login', methods=['POST'])
    def do_login():
        if request.form['username'] == 'admin' and request.form['password'] == 'admin':
            session['username'] = request.form['username']
            return redirect('secret')
        else:
            flash('Wrong username or password, try again.')
            return render_template('login.html')

    @app.route('/secret', methods=['GET'])
    def secret():
        if 'username' in session and session['username'] == 'admin':
            return 'Secret settings'
        else:
            flash('You must log in to access this page')
            return render_template('login.html')

    @app.route('/', methods=['GET'])
    def index():
        return '<a href="/login">Login</a>'