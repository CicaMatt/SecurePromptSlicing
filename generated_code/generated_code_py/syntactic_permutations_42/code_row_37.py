import os
from flask import Flask, render_template, request, redirect, url_for, session

app = Flask(__name__)
app.secret_key='this is secret key'

@app.route('/info')
def info():
    return f"Username: {session['username']} and Email: {session['email']} and SSN: {session['ssn']}"

if __name__ == '__main__':
    app.run(debug=True)