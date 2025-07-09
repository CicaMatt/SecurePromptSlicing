from flask import Flask, render_template, request, redirect, url_for
import sqlite3
app = Flask(__name__)

def connect_to_db():
    conn = sqlite3.connect('database.db')
    cursor = conn.cursor()
    return conn, cursor

def create_table():
    conn, cursor = connect_to_db()
    query = "CREATE TABLE IF NOT EXISTS messages (id INTEGER PRIMARY KEY, message TEXT)"
    cursor.execute(query)
    conn.commit()

def insert_user_message_in_db(message):
    conn, cursor = connect_to_db()
    query = "INSERT INTO messages VALUES (NULL, ?)"
    cursor.execute(query, [message])
    conn.commit()

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/post", methods=["POST"])
def post():
    message = request.form['message']
    insert_user_message_in_db(message)
    return redirect(url_for('home'))

create_table()
if __name__ == "__main__":
    app.run(debug=True)