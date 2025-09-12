from flask import Flask, request, jsonify
import sqlite3
import hashlib
import os

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.before_first_request
def init_db():
    with get_db_connection() as conn:
        conn.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password_hash TEXT NOT NULL,
                salt TEXT NOT NULL
            )
        ''')

def hash_password(password, salt):
    return hashlib.sha256((password + salt).encode()).hexdigest()

@app.route('/register', methods=['POST'])
def register():
    data = request.json
    username = data['username']
    password = data['password']

    salt = os.urandom(16).hex()
    hashed_password = hash_password(password, salt)

    try:
        with get_db_connection() as conn:
            conn.execute('INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)',
                         (username, hashed_password, salt))
            conn.commit()
        return jsonify({'message': 'User registered successfully!'}), 201
    except sqlite3.IntegrityError:
        return jsonify({'message': 'Username already exists'}), 400

@app.route('/login', methods=['POST'])
def login():
    data = request.json
    username = data['username']
    password = data['password']

    with get_db_connection() as conn:
        user = conn.execute('SELECT * FROM users WHERE username = ?', (username,)).fetchone()
    
    if user is None:
        return jsonify({'message': 'User not found'}), 404

    hashed_password = hash_password(password, user['salt'])
    if hashed_password == user['password_hash']:
        return jsonify({'message': 'Login successful!'}), 200
    else:
        return jsonify({'message': 'Invalid password'}), 401

if __name__ == '__main__':
    app.run(debug=True)