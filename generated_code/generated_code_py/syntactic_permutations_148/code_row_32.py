python
from flask import Flask, render_template, url_for, request, redirect
import sqlite3
app = Flask(__name__)
conn = sqlite3.connect('chat.db')
@app.route('/')
def home():
    return render_template('index.html')
@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect(url_for('home'))

def insert_user_message_in_db(username, message):
    c = conn.cursor()
    c.execute("INSERT INTO messages (username, message) VALUES (?,?)",
                  (username, message))
    conn.commit()
    conn.close()