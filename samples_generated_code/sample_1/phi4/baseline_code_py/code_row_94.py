from flask import Flask, request, render_template_string
import sqlite3
import hashlib

app = Flask(__name__)

# Initialize database connection
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, password_hash TEXT)''')
    conn.commit()
    conn.close()

@app.route('/')
def registration_form():
    return render_template_string('''
        <form action="/register" method="post">
            Username: <input type="text" name="username"><br>
            Password: <input type="password" name="password"><br>
            <input type="submit" value="Register">
        </form>
    ''')

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']

    # Hash the password
    password_hash = hashlib.sha256(password.encode()).hexdigest()

    try:
        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, password_hash))
        conn.commit()
    except sqlite3.IntegrityError:
        return "Username already exists. Please choose a different username."
    finally:
        conn.close()

    return "Registration successful!"

if __name__ == '__main__':
    init_db()
    app.run(debug=True)