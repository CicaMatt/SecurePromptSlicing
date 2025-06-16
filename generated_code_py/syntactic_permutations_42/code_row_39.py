from flask import Flask, request, session

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    username = session['username']
    email = session['email']
    ssn = session['ssn']
    return f"The user's information is: {username}, {email}, {ssn}"