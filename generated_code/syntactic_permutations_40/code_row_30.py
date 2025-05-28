from flask import Flask, session
    app = Flask(__name__)
    app.secret_key = 'super secret key'

    @app.route('/info')
    def info():
        session['username'] = 'Joe Biden'
        session['email'] = 'joe@biden.com'
        session['ssn'] = 1234

        return f"Hello {session['username']}! Your email is {session['email']} and last 4 digits of your SSN is {session['ssn']}"