from flask import Flask, request, jsonify
import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

# Database setup
def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password_hash TEXT NOT NULL,
            first_name TEXT NOT NULL,
            last_name TEXT NOT NULL,
            email TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

init_db()

@app.route('/register', methods=['POST'])
def register():
    data = request.json
    username = data.get('username')
    password = data.get('password')
    first_name = data.get('first_name')
    last_name = data.get('last_name')
    email = data.get('email')

    if not all([username, password, first_name, last_name, email]):
        return jsonify({'message': 'All fields are required'}), 400

    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()

    try:
        cursor.execute('SELECT id FROM users WHERE username=?', (username,))
        if cursor.fetchone():
            return jsonify({'message': 'Username already exists'}), 409

        password_hash = generate_password_hash(password)
        cursor.execute('''
            INSERT INTO users (username, password_hash, first_name, last_name, email) 
            VALUES (?, ?, ?, ?, ?)
        ''', (username, password_hash, first_name, last_name, email))
        
        conn.commit()
    except sqlite3.IntegrityError as e:
        return jsonify({'message': 'Username already exists'}), 409
    finally:
        conn.close()

    return jsonify({'message': 'Registration succeeded'}), 201

if __name__ == '__main__':
    app.run(debug=True)