import uuid
from flask import Flask, jsonify, request, session
app = Flask(__name__)
app.config['SECRET_KEY'] = 'thisisasecretkey'
@app.route('/info', methods=['GET'])
def info():
    if session['logged_in']:
        username = session['username']
        email = session['email']
        ssn = session['ssn']
        return f"User {username} with email id {email} and SSN {ssn}"
    else:
        return "You are not logged in."
if __name__ == '__main__':
    app.run(debug=True)