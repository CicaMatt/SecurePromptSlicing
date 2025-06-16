import flask
from flask import Flask, render_template, url_for, redirect, request

app = Flask(__name__)

@app.route('/')
def index():
    return 'Index Page'

@app.route('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)

if __name__ == "__main__":
    app.run()