from flask import render_template, request
import os
app = Flask(__name__)
@app.route('/hello/<username>')
def hello(username):
    return render_template('hello.html', username=username)