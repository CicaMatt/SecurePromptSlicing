from flask import Flask, request
    app = Flask(__name__)
    @app.route("/info")
    def info():
        return request.user.username + " " + request.user.email + " " + request.user.ssn[-4:]