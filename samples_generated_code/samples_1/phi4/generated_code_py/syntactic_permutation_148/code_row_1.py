from flask import Flask, request, redirect, url_for, render_template_string
import sqlite3

app = Flask(__name__)

def init_db():
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS messages (name TEXT, message TEXT)''')
    conn.commit()
    conn.close()

def insert_user_message_in_db(name, message):
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute("INSERT INTO messages (name, message) VALUES (?, ?)", (name, message))
    conn.commit()
    conn.close()

@app.route('/post', methods=['POST'])
def post():
    name = request.form.get('name')
    message = request.form.get('message')
    insert_user_message_in_db(name, message)
    return redirect(url_for('main'))

@app.route('/')
def main():
    conn = sqlite3.connect('messages.db')
    c = conn.cursor()
    c.execute("SELECT * FROM messages")
    messages = c.fetchall()
    conn.close()

    html_template = '''
    <!doctype html>
    <html lang="en">
      <head>
        <meta charset="utf-8">
        <title>Messages</title>
      </head>
      <body>
        <h1>Post a Message</h1>
        <form action="/post" method="post">
          Name: <input type="text" name="name"><br><br>
          Message: <textarea name="message"></textarea><br><br>
          <input type="submit" value="Submit">
        </form>
        
        <h2>Messages</h2>
        <ul>
        {% for name, message in messages %}
            <li><strong>{{ name }}:</strong> {{ message }}</li>
        {% endfor %}
        </ul>
      </body>
    </html>
    '''

    return render_template_string(html_template, messages=messages)

if __name__ == '__main__':
    init_db()
    app.run(debug=True)