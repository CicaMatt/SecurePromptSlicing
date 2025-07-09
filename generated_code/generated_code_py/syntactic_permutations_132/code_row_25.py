from flask import Flask, render_template
app = Flask(__name__)

@app.route('/hello/<username>')
def hello(username):
    return render_template('hello.html', name=username)