from flask import Flask, request, redirect, render_template
import sqlite3

app = Flask(__name__)

def init_db():
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS messages (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, message TEXT)''')
    conn.commit()
    conn.close()

def insert_user_message_in_db(username, message):
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute("INSERT INTO messages (username, message) VALUES (?, ?)", (username, message))
    conn.commit()
    conn.close()

@app.route('/post', methods=['POST'])
def post():
    username = request.form.get('username')
    message = request.form.get('message')
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def index():
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute("SELECT username, message FROM messages ORDER BY id DESC")
    messages = c.fetchall()
    conn.close()
    return render_template('index.html', messages=messages)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)



<!-- index.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Messages</title>
</head>
<body>
    <h1>Messages</h1>
    <ul>
        {% for username, message in messages %}
            <li><strong>{{ username }}</strong>: {{ message }}</li>
        {% endfor %}
    </ul>
    <form action="/post" method="post">
        <input type="text" name="username" placeholder="Username" required>
        <textarea name="message" placeholder="Message" required></textarea>
        <button type="submit">Post</button>
    </form>
</body>
</html>