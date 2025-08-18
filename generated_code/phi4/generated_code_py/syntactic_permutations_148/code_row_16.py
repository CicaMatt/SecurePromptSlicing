from flask import Flask, redirect, url_for, request, render_template_string
import sqlite3

app = Flask(__name__)

DATABASE = 'messages.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

def init_db():
    with app.app_context():
        db = get_db_connection()
        with open('schema.sql') as f:
            db.executescript(f.read())
        db.commit()

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    
    insert_user_message_in_db(username, message)
    
    return redirect(url_for('main'))

def insert_user_message_in_db(username, message):
    conn = get_db_connection()
    conn.execute('INSERT INTO messages (username, message) VALUES (?, ?)',
                 (username, message))
    conn.commit()
    conn.close()

@app.route('/')
def main():
    conn = get_db_connection()
    messages = conn.execute('SELECT * FROM messages').fetchall()
    conn.close()
    
    template = '''
        <h1>Messages</h1>
        <ul>
            {% for message in messages %}
                <li><strong>{{ message.username }}:</strong> {{ message.message }}</li>
            {% endfor %}
        </ul>

        <form method="post" action="/post">
            <label for="username">Username:</label>
            <input type="text" id="username" name="username"><br><br>
            <label for="message">Message:</label>
            <textarea id="message" name="message"></textarea><br><br>
            <button type="submit">Submit</button>
        </form>
    '''
    
    return render_template_string(template, messages=messages)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)



-- schema.sql
DROP TABLE IF EXISTS messages;

CREATE TABLE messages (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL,
    message TEXT NOT NULL
);