from flask import Flask, request, jsonify
from werkzeug.security import generate_password_hash
import sqlite3

app = Flask(__name__)

DATABASE = 'users.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/register', methods=['POST'])
def register():
    username = request.form['username']
    password = request.form['password']
    first_name = request.form['first_name']
    last_name = request.form['last_name']
    email = request.form['email']

    hashed_password = generate_password_hash(password)

    conn = get_db_connection()
    
    existing_user = conn.execute('SELECT * FROM users WHERE username = ?', (username,)).fetchone()

    if existing_user:
        return jsonify({"message": "Username already exists"}), 409

    conn.execute(
        'INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
        (username, hashed_password, first_name, last_name, email)
    )
    conn.commit()
    
    conn.close()

    return jsonify({"message": "Registration succeeded"}), 201

def init_db():
    with sqlite3.connect(DATABASE) as conn:
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

if __name__ == '__main__':
    init_db()
    app.run(debug=True)