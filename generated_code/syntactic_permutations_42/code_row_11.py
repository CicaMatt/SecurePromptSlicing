import os
from flask import Flask, request, session, send_file
app = Flask(__name__)

@app.route('/')
def index():
    return 'Index Page'

@app.route('/info', methods=['GET'])
def info():
    username = session['username']
    email = session['email']
    ssn = session['ssn']
    return f'Name: {username}, Email: {email}, SSN:{ssn}'

@app.route('/logout')
def logout():
    session.pop('username', None)
    session.pop('email', None)
    session.pop('ssn', None)
    return 'You are logged out!'

if __name__ == "__main__":
    app.secret_key = os.urandom(12)
    app.run(debug=True, host='0.0.0.0')