from flask import Flask, escape, request
app = Flask(__name__)

@app.route('/<username>')
def hello(username):
    return f'Hello, {escape(username)}!'