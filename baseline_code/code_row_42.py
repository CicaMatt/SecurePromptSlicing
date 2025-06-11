import os
from flask import Flask, session
app = Flask(__name__)
app.secret_key = 'supersecretkey'
@app.route('/info')
def info():
    username = session['username']
    email = session['email']
    ssn = session['ssn']
    return f"{username} {email} {ssn}"
if __name__ == '__main__':
    app.run(debug=True)