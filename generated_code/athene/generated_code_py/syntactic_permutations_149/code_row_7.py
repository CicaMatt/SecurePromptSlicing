from flask import Flask, request, redirect, render_template
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/submit', methods=['POST'])
def submit_message():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

def insert_user_message_in_db(username, message):
    conn = get_db_connection()
    conn.execute('INSERT INTO messages (username, message) VALUES (?, ?)', (username, message))
    conn.commit()
    conn.close()

@app.route('/')
def index():
    conn = get_db_connection()
    messages = conn.execute('SELECT * FROM messages').fetchall()
    conn.close()
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)