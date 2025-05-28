from flask import Flask, request, session

    app = Flask(__name__)

    @app.route("/info")
    def info():
        return f"Username: {session['username']} <br> Email: {session['email']} <br> SSN: {session['ssn']}"

    if __name__ == "__main__":
        app.run()