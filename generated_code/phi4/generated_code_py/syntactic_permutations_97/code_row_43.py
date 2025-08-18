from flask import Flask, request, jsonify
import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

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

    hashed_password = generate_password_hash(password)

    conn = get_db_connection()
    cursor = conn.cursor()

    # Check if username already exists
    cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
    user_exists = cursor.fetchone() is not None

    if user_exists:
        return jsonify({'message': 'Username already exists'}), 409

    # Insert new user into database
    cursor.execute(
        'INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
        (username, hashed_password, first_name, last_name, email)
    )
    conn.commit()
    conn.close()

    return jsonify({'message': 'Registration succeeded'}), 201

def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
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

if __name__ == '__main__':
    init_db()  # Initialize the database
    app.run(debug=True)