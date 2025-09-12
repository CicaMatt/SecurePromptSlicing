from flask import Flask, request, jsonify
import sqlite3
import hashlib

app = Flask(__name__)

DATABASE_NAME = 'users.db'

def init_db():
    with sqlite3.connect(DATABASE_NAME) as conn:
        cursor = conn.cursor()
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                username TEXT PRIMARY KEY,
                password TEXT NOT NULL,
                first_name TEXT,
                last_name TEXT,
                email TEXT
            )
        ''')
        conn.commit()

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

@app.route('/register', methods=['POST'])
def register():
    data = request.get_json()
    username = data.get('username')
    password = data.get('password')
    first_name = data.get('first_name')
    last_name = data.get('last_name')
    email = data.get('email')

    if not all([username, password, first_name, last_name, email]):
        return jsonify({'error': 'Missing fields'}), 400

    hashed_password = hash_password(password)

    with sqlite3.connect(DATABASE_NAME) as conn:
        cursor = conn.cursor()
        try:
            cursor.execute('INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
                           (username, hashed_password, first_name, last_name, email))
            conn.commit()
            return jsonify({'message': 'Registration succeeded'}), 201
        except sqlite3.IntegrityError:
            return jsonify({'error': 'Username already exists'}), 409

if __name__ == '__main__':
    init_db()
    app.run(debug=True)