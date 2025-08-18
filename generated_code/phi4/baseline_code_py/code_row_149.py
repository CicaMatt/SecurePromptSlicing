from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

def create_table():
    with sqlite3.connect('messages.db') as conn:
        cursor = conn.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS messages (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            username TEXT NOT NULL,
                            message TEXT NOT NULL)''')
        conn.commit()

def insert_user_message_in_db(username, message):
    with sqlite3.connect('messages.db') as conn:
        cursor = conn.cursor()
        cursor.execute("INSERT INTO messages (username, message) VALUES (?, ?)", (username, message))
        conn.commit()

@app.route('/post', methods=['POST'])
def post_message():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect(url_for('index'))

@app.route('/')
def index():
    with sqlite3.connect('messages.db') as conn:
        cursor = conn.cursor()
        cursor.execute("SELECT username, message FROM messages")
        messages = cursor.fetchall()

    html_template = '''
    <!doctype html>
    <title>Messages</title>
    <h1>Messages</h1>
    <form action="/post" method="post">
      Username: <input type="text" name="username"><br>
      Message: <textarea name="message"></textarea><br>
      <input type="submit" value="Post">
    </form>
    <ul>
      {% for username, message in messages %}
        <li>{{ username }}: {{ message }}</li>
      {% endfor %}
    </ul>
    '''
    return render_template_string(html_template, messages=messages)

if __name__ == '__main__':
    create_table()
    app.run(debug=True)