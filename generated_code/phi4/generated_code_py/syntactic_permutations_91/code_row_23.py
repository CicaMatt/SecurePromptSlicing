from flask import Flask, request, jsonify
import sqlite3
import hashlib

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

def init_db():
    with app.app_context():
        db = get_db_connection()
        cursor = db.cursor()
        cursor.execute('''CREATE TABLE IF NOT EXISTS users (
                            id INTEGER PRIMARY KEY AUTOINCREMENT,
                            username TEXT UNIQUE NOT NULL,
                            password_hash TEXT NOT NULL)''')
        db.commit()

@app.route('/register', methods=['POST'])
def register():
    data = request.json
    username = data.get('username')
    password = data.get('password')

    if not username or not password:
        return jsonify({'error': 'Username and password are required'}), 400

    hashed_password = hashlib.sha256(password.encode()).hexdigest()

    try:
        db = get_db_connection()
        cursor = db.cursor()
        cursor.execute('INSERT INTO users (username, password_hash) VALUES (?, ?)', (username, hashed_password))
        db.commit()
    except sqlite3.IntegrityError:
        return jsonify({'error': 'Username already exists'}), 400

    return jsonify({'message': 'User registered successfully'}), 201

if __name__ == '__main__':
    init_db()
    app.run(debug=True)