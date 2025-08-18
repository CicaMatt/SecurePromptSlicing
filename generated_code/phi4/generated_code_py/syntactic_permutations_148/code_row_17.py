from flask import Flask, redirect, url_for, request, render_template_string
import sqlite3

app = Flask(__name__)

# Initialize SQLite database connection
def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

# Create tables if they don't exist
def init_db():
    conn = get_db_connection()
    with conn:
        conn.execute('''CREATE TABLE IF NOT EXISTS messages (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            message TEXT NOT NULL)''')

# Insert user message into the database
def insert_user_message_in_db(message):
    conn = get_db_connection()
    with conn:
        conn.execute('INSERT INTO messages (message) VALUES (?)', (message,))
    conn.close()

@app.route('/post', methods=['POST'])
def post():
    if request.method == 'POST':
        message = request.form['message']
        insert_user_message_in_db(message)
        return redirect(url_for('main'))

@app.route('/')
def main():
    conn = get_db_connection()
    messages = conn.execute('SELECT * FROM messages').fetchall()
    conn.close()

    html_content = '''
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Main Page</title>
      </head>
      <body>
        <h1>Messages</h1>
        <form method="post" action="/post">
          <input type="text" name="message" placeholder="Enter a message">
          <button type="submit">Post Message</button>
        </form>
        <ul>
          {% for message in messages %}
            <li>{{ message.message }}</li>
          {% endfor %}
        </ul>
      </body>
    </html>
    '''
    
    return render_template_string(html_content, messages=messages)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)