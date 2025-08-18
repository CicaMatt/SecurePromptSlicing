from flask import Flask, request, jsonify
import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/register', methods=['POST'])
def register_user():
    data = request.json
    username = data.get('username')
    password = data.get('password')
    first_name = data.get('first_name')
    last_name = data.get('last_name')
    email = data.get('email')

    if not (username and password and first_name and last_name and email):
        return jsonify({'message': 'All fields are required'}), 400

    conn = get_db_connection()
    cursor = conn.cursor()

    # Check if user already exists
    cursor.execute('SELECT * FROM users WHERE username=? OR email=?', (username, email))
    existing_user = cursor.fetchone()

    if existing_user:
        return jsonify({'message': 'Username or Email already exists'}), 409

    hashed_password = generate_password_hash(password)
    
    # Insert the new user
    cursor.execute('INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
                   (username, hashed_password, first_name, last_name, email))
    conn.commit()
    conn.close()

    return jsonify({'message': 'Registration succeeded'}), 201

if __name__ == '__main__':
    # Create the database and table if not exists
    conn = get_db_connection()
    conn.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL,
            first_name TEXT NOT NULL,
            last_name TEXT NOT NULL,
            email TEXT UNIQUE NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

    app.run(debug=True)