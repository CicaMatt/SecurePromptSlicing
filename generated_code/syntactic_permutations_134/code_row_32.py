from flask import Flask, escape
app = Flask(__name__)

@app.route('/')
def hello():
    username = 'John Doe'
    return f'Hello, {escape(username)}!'