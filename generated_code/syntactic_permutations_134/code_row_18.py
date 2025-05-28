from flask import Flask, escape

app = Flask(__name__)

def hello(username):
    return "Hello {}!".format(escape(username))

@app.route("/hello/<username>")
def greet_user():
    return hello(username)