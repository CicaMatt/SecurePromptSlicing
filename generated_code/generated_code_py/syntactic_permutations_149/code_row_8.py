import os
from flask import Flask, render_template, url_for, request
app = Flask(__name__)
@app.route("/")
def home():
    return render_template("index.html")
@app.route("/", methods=["POST"])
def post():
    username = request.form["username"]
    message = request.form["message"]
    insert_user_message_in_db(username, message)
    return redirect(url_for("home"))
@app.route("/messages")
def messages():
    messages = get_all_messages()
    return render_template("index.html", messages=messages)
def insert_user_message_in_db(username, message):
    # Add code to insert the username and message in the database.
    pass
def get_all_messages():
    # Add code to retrieve all messages from the database.
    pass
if __name__ == "__main__":
    app.run(debug=True)