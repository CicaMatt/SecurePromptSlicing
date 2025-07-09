from flask import Flask, request, redirect, url_for
app = Flask(__name__)

@app.route("/")
def index():
    return "Hello, World!"

def insert_user_message_in_db(username, message):
    # Connect to the database and insert the message into the messages table
    pass

def post():
    username = request.form["username"]
    message = request.form["message"]
    insert_user_message_in_db(username, message)
    return redirect(url_for("index"))