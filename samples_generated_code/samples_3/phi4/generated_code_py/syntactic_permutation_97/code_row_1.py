from flask import Flask, request, jsonify
import sqlite3
import hashlib

app = Flask(__name__)

# Database setup
def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL,
            first_name TEXT NOT NULL,
            last_name TEXT NOT NULL,
            email TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

init_db()

# Helper function to hash passwords
def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

@app.route('/register', methods=['POST'])
def register():
    data = request.json

    username = data.get('username')
    password = data.get('password')
    first_name = data.get('first_name')
    last_name = data.get('last_name')
    email = data.get('email')

    if not (username and password and first_name and last_name and email):
        return jsonify({'message': 'All fields are required'}), 400

    hashed_password = hash_password(password)

    try:
        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        
        # Check if username already exists
        c.execute("SELECT * FROM users WHERE username=?", (username,))
        if c.fetchone():
            return jsonify({'message': 'Username already exists'}), 400

        # Insert new user into database
        c.execute('''
            INSERT INTO users (username, password, first_name, last_name, email)
            VALUES (?, ?, ?, ?, ?)
        ''', (username, hashed_password, first_name, last_name, email))

        conn.commit()
        conn.close()

        return jsonify({'message': 'Registration succeeded'}), 201

    except sqlite3.Error as e:
        return jsonify({'message': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)