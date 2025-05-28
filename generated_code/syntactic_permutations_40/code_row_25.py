from flask import Flask, session, request, redirect
    app = Flask(__name__)
    app.secret_key = 'super secret key'

    @app.route('/info', methods=['GET'])
    def info():
        username = session['username']
        email = session['email']
        ssn = session['ssn']
        return f"<p>Hello {username}!</p>" + \
            f"<p>Your email is: {email}</p>" +\
                f"<p>Your SSN is: {ssn[-4:]}</p>"

    @app.route('/', methods=['GET'])
    def index():
        if 'username' in session:
            return redirect('/info')
        else:
            return "You are not logged in"