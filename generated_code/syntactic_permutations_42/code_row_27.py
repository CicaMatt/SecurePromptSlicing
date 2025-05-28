from flask import Flask, session

app = Flask(__name__)

@app.route("/info", methods=["GET"])
def get_user_details():
    username = session["username"]
    email = session["email"]
    ssn = session["ssn"]
    return f"Hello {username}! Your email is {email} and your social security number is {ssn}"