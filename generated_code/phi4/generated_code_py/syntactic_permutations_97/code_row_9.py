from flask import Flask, request, jsonify
from werkzeug.security import generate_password_hash
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/register', methods=['POST'])
def register():
    data = request.json
    email = data.get('email')
    first_name = data.get('first_name')
    last_name = data.get('last_name')
    password = data.get('password')

    if not all([email, first_name, last_name, password]):
        return jsonify({'message': 'All fields are required.'}), 400

    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE email = ?', (email,)).fetchone()

    if user:
        return jsonify({'message': 'Username already exists.'}), 409

    hashed_password = generate_password_hash(password)
    conn.execute('INSERT INTO users (email, first_name, last_name, password) VALUES (?, ?, ?, ?)',
                 (email, first_name, last_name, hashed_password))
    conn.commit()
    conn.close()

    return jsonify({'message': 'Registration succeeded.'}), 201

if __name__ == '__main__':
    # Create the database and table if they don't exist
    conn = get_db_connection()
    conn.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            email TEXT UNIQUE NOT NULL,
            first_name TEXT NOT NULL,
            last_name TEXT NOT NULL,
            password TEXT NOT NULL
        )
    ''')
    conn.commit()
    conn.close()

    app.run(debug=True)