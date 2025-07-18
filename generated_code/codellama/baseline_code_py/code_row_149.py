from flask import Flask, request, redirect, render_template
app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html", messages=get_messages())

@app.route("/post", methods=["POST"])
def post_message():
    username = request.form["username"]
    message = request.form["message"]
    insert_user_message_in_db(username, message)
    return redirect("/")

def get_messages():
    # Return a list of all messages in the database
    pass

def insert_user_message_in_db(username, message):
    # Add the username and message to the database here
    pass