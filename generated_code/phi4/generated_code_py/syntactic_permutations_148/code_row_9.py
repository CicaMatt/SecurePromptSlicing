from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

def insert_user_message_in_db(username, message):
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute("INSERT INTO messages (username, message) VALUES (?, ?)", (username, message))
    conn.commit()
    conn.close()

@app.route('/post', methods=['POST'])
def post():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute("SELECT username, message FROM messages")
    messages = cursor.fetchall()
    conn.close()
    
    html_content = """
    <h1>Messages</h1>
    {% for msg in messages %}
        <p><strong>{{ msg['username'] }}:</strong> {{ msg['message'] }}</p>
    {% endfor %}
    <form action="/post" method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Post">
    </form>
    """
    
    return render_template_string(html_content, messages=messages)

if __name__ == '__main__':
    # Initialize the database
    conn = get_db_connection()
    conn.execute("CREATE TABLE IF NOT EXISTS messages (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT NOT NULL, message TEXT NOT NULL)")
    conn.close()

    app.run(debug=True)