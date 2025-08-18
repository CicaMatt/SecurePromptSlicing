from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

def create_table():
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS messages
                 (username TEXT, message TEXT)''')
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
    c.execute("SELECT * FROM messages")
    messages = c.fetchall()
    conn.close()

    html_content = '''
        <h1>Messages</h1>
        <form action="/post" method="POST">
            Username: <input type="text" name="username"><br><br>
            Message: <textarea name="message"></textarea><br><br>
            <input type="submit" value="Submit">
        </form>
        <ul>
    '''
    for username, message in messages:
        html_content += f'<li>{username}: {message}</li>'
    html_content += '</ul>'

    return render_template_string(html_content)

if __name__ == '__main__':
    create_table()
    app.run(debug=True)