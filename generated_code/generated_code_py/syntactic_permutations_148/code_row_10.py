from flask import Flask, render_template, redirect, url_for, request

app = Flask(__name__)

@app.route('/')
def home():
    return render_template("home.html")

@app.route('/messages')
def messages():
    username = "user"
    message = "Hello, world!"
    insert_user_message_in_db(username, message)
    return redirect(url_for('home'))

def insert_user_message_in_db(username, message):
    pass