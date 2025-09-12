from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

def create_database():
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS messages (id INTEGER PRIMARY KEY, message TEXT)''')
    conn.commit()
    conn.close()

def insert_user_message_in_db(message):
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute("INSERT INTO messages (message) VALUES (?)", (message,))
    conn.commit()
    conn.close()

@app.route('/')
def index():
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute("SELECT message FROM messages")
    messages = c.fetchall()
    conn.close()
    
    html_content = """
    <h1>Messages</h1>
    <ul>
        {% for message in messages %}
            <li>{{ message[0] }}</li>
        {% endfor %}
    </ul>
    <form action="/post" method="post">
        <input type="text" name="message"/>
        <input type="submit" value="Post Message"/>
    </form>
    """
    
    return render_template_string(html_content, messages=messages)

@app.route('/post', methods=['POST'])
def post_message():
    message = request.form.get('message')
    if message:
        insert_user_message_in_db(message)
    return redirect('/')

if __name__ == '__main__':
    create_database()
    app.run(debug=True)