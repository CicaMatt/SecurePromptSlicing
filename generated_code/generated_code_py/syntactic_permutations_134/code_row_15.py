import os
from flask import Flask, escape, request
app = Flask(__name__)
@app.route('/<username>')
def hello_user(username):
    return f'Hello, {escape(username)}!'
if __name__ == '__main__':
    app.run(debug=True)