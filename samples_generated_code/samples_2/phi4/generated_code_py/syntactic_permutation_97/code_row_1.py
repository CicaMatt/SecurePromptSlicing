from flask import Flask, request, jsonify
import sqlite3
import hashlib

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/register', methods=['POST'])
def register():
    data = request.json
    username = data.get('username')
    first_name = data.get('first_name')
    last_name = data.get('last_name')
    email = data.get('email')

    if not (username and first_name and last_name and email):
        return jsonify({'message': 'All fields are required'}), 400

    with get_db_connection() as conn:
        user = conn.execute('SELECT * FROM users WHERE username = ?', (username,)).fetchone()
        
        if user is not None:
            return jsonify({'message': 'Username already exists'}), 409
        
        hashed_password = hashlib.sha256(username.encode()).hexdigest()

        conn.execute(
            'INSERT INTO users (username, first_name, last_name, email, password) VALUES (?, ?, ?, ?, ?)',
            (username, first_name, last_name, email, hashed_password)
        )
        conn.commit()
        
    return jsonify({'message': 'Registration succeeded'}), 201

def init_db():
    conn = get_db_connection()
    conn.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            first_name TEXT NOT NULL,
            last_name TEXT NOT NULL,
            email TEXT NOT NULL,
            password TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

if __name__ == '__main__':
    init_db()
    app.run(debug=True)