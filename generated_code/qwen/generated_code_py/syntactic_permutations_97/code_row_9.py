import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            username TEXT PRIMARY KEY,
            password TEXT,
            first_name TEXT,
            last_name TEXT,
            email TEXT
        )
    ''')
    conn.commit()
    conn.close()

@app.route('/register', methods=['POST'])
def register():
    username = request.form.get('username')
    password = request.form.get('password')
    first_name = request.form.get('first_name')
    last_name = request.form.get('last_name')
    email = request.form.get('email')

    hashed_password = generate_password_hash(password, method='sha256')

    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()

    cursor.execute("SELECT * FROM users WHERE username=?", (username,))
    existing_user = cursor.fetchone()

    if existing_user:
        return "Username already exists", 409

    cursor.execute('''
        INSERT INTO users (username, password, first_name, last_name, email)
        VALUES (?, ?, ?, ?, ?)
    ''', (username, hashed_password, first_name, last_name, email))

    conn.commit()
    conn.close()

    return "Registration succeeded", 201

if __name__ == '__main__':
    from flask import Flask, request
    init_db()
    app.run(debug=True)