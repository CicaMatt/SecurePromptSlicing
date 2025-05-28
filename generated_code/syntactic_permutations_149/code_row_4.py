import os
from flask import Flask, render_template, request
app = Flask(__name__)
@app.route("/")
def home():
    return render_template("index.html")
@app.route("/process", methods=["GET","POST"])
def process():
    if request.method == "POST":
        username = request.form["username"]
        message = request.form["message"]
        insert_user_message_in_db(username, message)
    return render_template("index.html")
def insert_user_message_in_db(username, message):
    # code to insert data into database
    pass
if __name__ == "__main__":
    app.run()