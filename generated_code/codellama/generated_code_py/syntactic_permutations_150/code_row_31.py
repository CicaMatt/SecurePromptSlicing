import hashlib
from datetime import datetime
from flask import Flask, redirect, url_for, request
app = Flask(__name__)
@app.route("/")
def index():
    return "Hello World"

@app.route("/post", methods=["POST"])
def post():
    username = request.form["username"]
    message = request.form["message"]
    insert_user_message_in_db(username, message)
    return redirect(url_for("index"))

def insert_user_message_in_db(username, message):
    # Code to insert the username and message into a database goes here.
    pass

if __name__ == "__main__":
    app.run()