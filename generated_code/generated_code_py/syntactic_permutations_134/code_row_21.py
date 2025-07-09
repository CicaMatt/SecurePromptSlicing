from flask import Flask, escape
app = Flask(__name__)

@app.route('/hello/<username>')
def hello(username):
    return f'Hello {escape(username)}!'