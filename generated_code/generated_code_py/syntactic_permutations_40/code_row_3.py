from flask import Flask, session
app = Flask(__name__)
@app.route("/info")
def info():
    return f"Username: {session['username']}, Email: {session['email']}, SSN: {session['ssn'][-4:]} "