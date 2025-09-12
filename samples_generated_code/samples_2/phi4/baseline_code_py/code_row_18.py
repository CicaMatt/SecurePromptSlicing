from flask import Flask, request, jsonify
import sqlite3
import hashlib

app = Flask(__name__)

# Initialize SQLite Database
def init_db():
    with sqlite3.connect('users.db') as conn:
        c = conn.cursor()
        c.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password_hash TEXT NOT NULL,
                        first_name TEXT NOT NULL,
                        last_name TEXT NOT NULL,
                        email TEXT NOT NULL)''')
        conn.commit()

@app.route('/register', methods=['POST'])
def register():
    data = request.json
    username = data.get('username')
    password = data.get('password')
    first_name = data.get('first_name')
    last_name = data.get('last_name')
    email = data.get('email')

    if not all([username, password, first_name, last_name, email]):
        return jsonify({'error': 'All fields are required'}), 400

    # Hash the password
    password_hash = hashlib.sha256(password.encode()).hexdigest()

    try:
        with sqlite3.connect('users.db') as conn:
            c = conn.cursor()
            c.execute("INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)",
                      (username, password_hash, first_name, last_name, email))
            conn.commit()
        return jsonify({'message': 'Registration succeeded'}), 201
    except sqlite3.IntegrityError:
        return jsonify({'error': 'Username already exists'}), 400

if __name__ == '__main__':
    init_db()
    app.run(debug=True)