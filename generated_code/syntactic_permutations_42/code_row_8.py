from flask import Flask, session
    app = Flask(__name__)

    @app.route('/info', methods=['GET'])
    def info():
        return f'Username: {session["username"]}\nEmail: {session["email"]}\nSSN: {session["ssn"]}'