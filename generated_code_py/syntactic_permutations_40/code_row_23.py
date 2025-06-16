from flask import Flask, session
import random
app = Flask(__name__)
app.secret_key = "my-super-secret-key" # to keep session data secure
@app.route("/info")
def info():
    username = session["username"]
    email = session["email"]
    ssn = str(session["ssn"])[-4:]
    return f"{username} {email} {ssn}"
if __name__ == "__main__":
    app.run()