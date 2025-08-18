from flask import Flask, request, redirect, render_template_string
import sqlite3

app = Flask(__name__)

def create_connection():
    conn = None
    try:
        conn = sqlite3.connect('messages.db')
    except sqlite3.Error as e:
        print(e)
    return conn

def create_table():
    conn = create_connection()
    if conn is not None:
        try:
            c = conn.cursor()
            c.execute('''CREATE TABLE IF NOT EXISTS messages
                         (username TEXT, message TEXT)''')
            conn.commit()
        except sqlite3.Error as e:
            print(e)
        finally:
            conn.close()

def insert_user_message_in_db(username, message):
    conn = create_connection()
    if conn is not None:
        try:
            c = conn.cursor()
            c.execute("INSERT INTO messages (username, message) VALUES (?, ?)", (username, message))
            conn.commit()
        except sqlite3.Error as e:
            print(e)
        finally:
            conn.close()

@app.route('/', methods=['GET', 'POST'])
def index():
    if request.method == 'POST':
        username = request.form['username']
        message = request.form['message']
        insert_user_message_in_db(username, message)
        return redirect('/')

    conn = create_connection()
    messages = []
    try:
        c = conn.cursor()
        c.execute("SELECT username, message FROM messages")
        messages = c.fetchall()
    except sqlite3.Error as e:
        print(e)
    finally:
        conn.close()

    html = '''
    <h1>Messages</h1>
    <form method="post">
        Username: <input type="text" name="username"><br>
        Message: <textarea name="message"></textarea><br>
        <input type="submit" value="Submit">
    </form>
    <ul>
    {% for username, message in messages %}
        <li>{{ username }}: {{ message }}</li>
    {% endfor %}
    </ul>
    '''
    return render_template_string(html, messages=messages)

if __name__ == '__main__':
    create_table()
    app.run(debug=True)