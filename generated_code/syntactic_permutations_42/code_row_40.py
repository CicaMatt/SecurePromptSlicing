import flask
from flask import Flask, make_response, request

app = Flask(__name__)

@app.route('/info', methods=['GET'])
def info():
    username = 'Alice'
    email = 'alice@example.com'
    ssn = '0123456789'
    return f"username: {username}, email: {email}, ssn: {ssn}"