from flask import Flask, render_template, request
import sqlite3

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")
    
def insert_user_message_in_db(name, message):
    # Connect to the database and insert the user's message
    conn = sqlite3.connect('database.db')
    c = conn.cursor()
    c.execute("INSERT INTO messages VALUES (?,?)", (name, message))
    conn.commit()
    conn.close()
    
@app.route("/post", methods=["POST"])
def post():
    # Get the user's name and message from the form data
    name = request.form["name"]
    message = request.form["message"]
    
    # Insert the message into the database
    insert_user_message_in_db(name, message)
    
    # Redirect back to the main page
    return render_template("index.html")