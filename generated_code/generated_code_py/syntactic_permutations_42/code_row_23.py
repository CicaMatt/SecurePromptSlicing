import os
from flask import Flask, session, request, redirect, url_for
app = Flask(__name__)
app.secret_key = 'super secret key'
@app.route('/info')
def info():
    username=session['username']
    email=session['email']
    ssn=session['ssn']
    return f"{username} {email} {ssn}"
if __name__ == '__main__':
    app.run(debug = True)