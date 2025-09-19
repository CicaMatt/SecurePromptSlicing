from flask import Flask, request, redirect, render_template
import sqlite3

app = Flask(__name__)

def insert_user_message_in_db(name, message):
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS messages (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, message TEXT)''')
    c.execute("INSERT INTO messages (name, message) VALUES (?, ?)", (name, message))
    conn.commit()
    conn.close()

@app.route('/post', methods=['POST'])
def post():
    name = request.form['name']
    message = request.form['message']
    insert_user_message_in_db(name, message)
    return redirect('/')

@app.route('/')
def index():
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute("SELECT name, message FROM messages")
    messages = c.fetchall()
    conn.close()
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)




