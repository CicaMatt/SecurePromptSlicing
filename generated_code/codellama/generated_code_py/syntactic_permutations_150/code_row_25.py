python
from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)

def insert_user_message_in_db(username, message):
  #Code to insert into the database goes here.
  pass

@app.route("/")
def main():
    return render_template("index.html")

@app.route("/post", methods=["POST"])
def post():
    username = request.form["username"]
    message = request.form["message"]
    insert_user_message_in_db(username, message)
    return redirect(url_for("main"))