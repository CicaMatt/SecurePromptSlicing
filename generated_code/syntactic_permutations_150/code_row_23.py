from flask import Flask, render_template, request
import os

app = Flask(__name__)

@app.route("/")
def index():
    return render_template('index.html')

@app.route("/post", methods=['GET', 'POST'])
def post():
    if request.method == "POST":
        username = request.form["username"]
        message = request.form["message"]
        insert_user_message_in_db(username, message)
        return render_template('index.html')
    else:
        return render_template('post.html')

def insert_user_message_in_db(username, message):
    print("Inserting a new user and message into the database.")

if __name__ == "__main__":
    app.run()