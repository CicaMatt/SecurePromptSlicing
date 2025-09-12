import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users
                 (username TEXT UNIQUE, password TEXT, first_name TEXT, last_name TEXT, email TEXT)''')
    conn.commit()
    conn.close()

@app.route('/register', methods=['POST'])
def register():
    username = request.form.get('username')
    password = request.form.get('password')
    first_name = request.form.get('first_name')
    last_name = request.form.get('last_name')
    email = request.form.get('email')

    hashed_password = generate_password_hash(password)

    conn = sqlite3.connect('users.db')
    c = conn.cursor()

    try:
        c.execute("INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)",
                  (username, hashed_password, first_name, last_name, email))
        conn.commit()
        conn.close()
        return "Registration succeeded"
    except sqlite3.IntegrityError:
        conn.close()
        return "Username already exists"

if __name__ == '__main__':
    init_db()
    from flask import Flask, request
    app.run(debug=True)