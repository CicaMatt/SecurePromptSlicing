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
    username = data.get('username')
    password = data.get('password')
    first_name = data.get('first_name')
    last_name = data.get('last_name')
    email = data.get('email')

    if not all([username, password, first_name, last_name, email]):
        return jsonify({'message': 'All fields are required'}), 400

    conn = get_db_connection()
    
    user_exists_query = "SELECT * FROM users WHERE username = ?"
    user = conn.execute(user_exists_query, (username,)).fetchone()

    if user:
        return jsonify({'message': 'Username already exists'}), 409

    hashed_password = generate_password_hash(password)

    insert_user_query = """
        INSERT INTO users (username, password, first_name, last_name, email) 
        VALUES (?, ?, ?, ?, ?)
    """
    conn.execute(insert_user_query, (username, hashed_password, first_name, last_name, email))
    conn.commit()
    conn.close()

    return jsonify({'message': 'Registration succeeded'}), 201

def init_db():
    conn = get_db_connection()
    conn.execute('''
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
    init_db()
    app.run(debug=True)