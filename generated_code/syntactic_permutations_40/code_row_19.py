from flask import Flask, session
    app = Flask(__name__)
    @app.route('/info')
    def info():
      return "Username:" + session["username"] + "<br>Email:" + session["email"] + "<br>SSN:" + session["ssn"][-4:]