from flask import Flask, session
app = Flask(__name__)

@app.route('/info')
def info():
    return f"Name: {session['username']} Email: {session['email']}"