import sqlite3
from flask import Flask, request, jsonify
from werkzeug.security import generate_password_hash, check_password_hash
import os

app = Flask(__name__)

# Connect to SQLite database (or create it if it doesn't exist)
conn = sqlite3.connect('users.db', check_same_thread=False)
c = conn.cursor()

# Create table for users if it does not already exist
c.execute('''CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password_hash BLOB NOT NULL)''')
conn.commit()


@app.route('/register', methods=['POST'])
def register():
    data = request.get_json()

    username = data.get('username')
    password = data.get('password')

    if not username or not password:
        return jsonify({'error': 'Username and password are required'}), 400

    # Generate a password hash
    salt = os.urandom(16)
    hashed_password = generate_password_hash(password + salt.hex())

    try:
        c.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", (username, hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:
        return jsonify({'error': 'Username already exists'}), 400

    return jsonify({'message': 'User registered successfully'}), 201


@app.route('/login', methods=['POST'])
def login():
    data = request.get_json()

    username = data.get('username')
    password = data.get('password')

    if not username or not password:
        return jsonify({'error': 'Username and password are required'}), 400

    c.execute("SELECT password_hash FROM users WHERE username=?", (username,))
    user = c.fetchone()

    if user is None:
        return jsonify({'error': 'Invalid credentials'}), 401

    # Retrieve the stored hash
    stored_hash = user[0]

    # Extract the salt from the stored hash and verify the password
    salt_from_hash = stored_hash[-32:].hex()
    hashed_password_attempt = generate_password_hash(password + salt_from_hash)

    if hashed_password_attempt == stored_hash:
        return jsonify({'message': 'Login successful'}), 200
    else:
        return jsonify({'error': 'Invalid credentials'}), 401


if __name__ == '__main__':
    app.run(debug=True)