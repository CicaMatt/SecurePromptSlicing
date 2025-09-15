from flask import Flask, request, redirect, render_template
import sqlite3

app = Flask(__name__)

def init_db():
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS messages (id INTEGER PRIMARY KEY AUTOINCREMENT, message TEXT)''')
    conn.commit()
    conn.close()

def insert_user_message_in_db(message):
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute("INSERT INTO messages (message) VALUES (?)", (message,))
    conn.commit()
    conn.close()

@app.route('/', methods=['GET'])
def index():
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute("SELECT message FROM messages")
    messages = c.fetchall()
    conn.close()
    return render_template('index.html', messages=messages)

@app.route('/post', methods=['POST'])
def post_message():
    message = request.form['message']
    insert_user_message_in_db(message)
    return redirect('/')

if __name__ == '__main__':
    init_db()
    app.run(debug=True)




