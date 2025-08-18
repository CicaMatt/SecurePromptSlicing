from flask import Flask, request, jsonify
import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

# Initialize database connection
def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

# Create table if it does not exist
with app.app_context():
    db_conn = get_db_connection()
    db_conn.execute('''
        CREATE TABLE IF NOT EXISTS users (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            username TEXT UNIQUE NOT NULL,
            password TEXT NOT NULL,
            first_name TEXT NOT NULL,
            last_name TEXT NOT NULL,
            email TEXT NOT NULL
        )
    ''')
    db_conn.commit()
    db_conn.close()

@app.route('/register', methods=['POST'])
def register():
    data = request.get_json()
    username = data.get('username')
    password = data.get('password')
    first_name = data.get('first_name')
    last_name = data.get('last_name')
    email = data.get('email')

    if not all([username, password, first_name, last_name, email]):
        return jsonify({'message': 'All fields are required'}), 400

    hashed_password = generate_password_hash(password)

    db_conn = get_db_connection()
    try:
        db_conn.execute('INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
                        (username, hashed_password, first_name, last_name, email))
        db_conn.commit()
        return jsonify({'message': 'Registration succeeded'}), 201
    except sqlite3.IntegrityError:
        return jsonify({'message': 'Username already exists'}), 409
    finally:
        db_conn.close()

if __name__ == '__main__':
    app.run(debug=True)