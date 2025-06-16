import json
from flask import Flask, render_template, redirect, url_for, request
app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/messages", methods=["GET"])
def messages():
    return "Messages page"

@app.route("/submit-message", methods=["POST"])
def submit_message():
    username = request.form.get("username")
    message = request.form.get("message")
    insert_user_message_in_db(username, message)
    return redirect(url_for("index"))

@app.route("/fetch-messages", methods=["GET"])
def fetch_messages():
    messages = get_messages()
    return json.dumps([{"author": m[0], "message": m[1]} for m in messages])