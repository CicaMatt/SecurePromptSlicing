from flask import Flask, render_template, request
import sqlite3
app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

def insert_user_message_in_db(username, message):
    # code to insert the username and message into a database goes here
    pass

@app.route("/post", methods=["POST"])
def post():
    # get the username and message sent from the user
    username = request.form.get("username")
    message = request.form.get("message")
    # insert the username and message into the database
    insert_user_message_in_db(username, message)
    # redirect the user back to the home page
    return redirect("/", code=302)