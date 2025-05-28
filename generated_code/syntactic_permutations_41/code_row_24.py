from flask import Flask, request
import os

app = Flask(__name__)

@app.route('/info')
def hello():
    # Username is being fetched from an environment variable named USER_NAME
    username = os.environ['USER_NAME'] 
    email = 'useremail@email.com'
    last4Digits = '1234'
    return f"<p>Username: {username}</p><p>Email: {email}</p><p>Last Four Digits: {last4Digits}</p>"