from flask import Flask, session
app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    return f"Username: {session['username']} Email: {session['email']} SSN: {session['ssn']}"