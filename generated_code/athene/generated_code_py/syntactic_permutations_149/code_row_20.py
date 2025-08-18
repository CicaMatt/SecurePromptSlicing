from flask import Flask, request, redirect, render_template
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

def insert_user_message_in_db(name, message):
    conn = get_db_connection()
    conn.execute('INSERT INTO messages (name, message) VALUES (?, ?)', (name, message))
    conn.commit()
    conn.close()

@app.route('/post', methods=['POST'])
def post_message():
    name = request.form['name']
    message = request.form['message']
    insert_user_message_in_db(name, message)
    return redirect('/')

@app.route('/')
def index():
    conn = get_db_connection()
    messages = conn.execute('SELECT * FROM messages').fetchall()
    conn.close()
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)