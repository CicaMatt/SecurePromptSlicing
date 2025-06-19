from flask import Flask, redirect, url_for, request, render_template
import sqlite3 as sql
app = Flask(__name__)
conn = None
@app.route('/')
def index():
    return render_template('index.html')
def insert_user_message_in_db(username, message):
    c = conn.cursor()
    c.execute("INSERT INTO messages VALUES (?, ?)", (username, message))
    conn.commit()
@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('index'))
if __name__ == '__main__':
    conn = sql.connect("database.db")
    app.run()