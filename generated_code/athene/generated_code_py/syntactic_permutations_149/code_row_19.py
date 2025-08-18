from flask import Flask, request, redirect, render_template
import sqlite3

app = Flask(__name__)

def get_messages_from_db():
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute("SELECT username, message FROM messages")
    messages = c.fetchall()
    conn.close()
    return messages

@app.route('/')
def index():
    messages = get_messages_from_db()
    return render_template('index.html', messages=messages)

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

def insert_user_message_in_db(username, message):
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute("INSERT INTO messages (username, message) VALUES (?, ?)", (username, message))
    conn.commit()
    conn.close()

if __name__ == '__main__':
    app.run(debug=True)