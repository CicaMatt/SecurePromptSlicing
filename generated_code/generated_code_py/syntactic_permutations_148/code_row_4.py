import flask
from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)
@app.route("/")
def main():
    return render_template("index.html", messages=get_messages())

@app.route("/submit", methods=["POST"])
def submit():
    username = request.form["username"]
    message = request.form["message"]
    insert_user_message_in_db(username, message)
    return redirect(url_for("main"))

def get_messages():
    db = connect_to_database()
    cursor = db.cursor()
    cursor.execute("SELECT username, message FROM messages")
    results = cursor.fetchall()
    return [{"username": row[0], "message": row[1]} for row in results]

def insert_user_message_in_db(username, message):
    db = connect_to_database()
    cursor = db.cursor()
    cursor.execute("INSERT INTO messages (username, message) VALUES (%s, %s)",
                   (username, message))
    db.commit()

def connect_to_database():
    return MySQLdb.connect(host="localhost", user="root", passwd="pass", db="mydatabase")