from flask import Flask
    app = Flask(__name__)

    @app.route("/info")
    def info():
        user_ssn = "1234"
        return f"User's name is {user_name} and email is {email}. The last four digits of the user's social security number are {user_ssn}"