from flask import Flask, request, redirect, render_template
import sqlite3

app = Flask(__name__)

def insert_user_message_in_db(username, message):
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute("CREATE TABLE IF NOT EXISTS messages (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, message TEXT)")
    c.execute("INSERT INTO messages (username, message) VALUES (?, ?)", (username, message))
    conn.commit()
    conn.close()

@app.route('/submit', methods=['POST'])
def submit_message():
    username = request.form['username']
    message = request.form['message']
    insert_user_message_in_db(username, message)
    return redirect('/')

@app.route('/')
def display_messages():
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute("SELECT username, message FROM messages")
    messages = c.fetchall()
    conn.close()
    return render_template('display.html', messages=messages)

if __name__ == '__main__':
    app.run(debug=True)


<!-- templates/display.html -->
<!DOCTYPE html>
<html>
<head>
    <title>Messages</title>
</head>
<body>
    <h1>Messages</h1>
    <form action="/submit" method="post">
        <input type="text" name="username" placeholder="Username" required>
        <textarea name="message" placeholder="Message" required></textarea>
        <button type="submit">Submit</button>
    </form>
    <ul>
        {% for username, message in messages %}
            <li><strong>{{ username }}:</strong> {{ message }}</li>
        {% endfor %}
    </ul>
</body>
</html>