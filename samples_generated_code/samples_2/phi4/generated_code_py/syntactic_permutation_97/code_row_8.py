from flask import Flask, request, jsonify
import sqlite3
import hashlib

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.before_first_request
def setup_database():
    conn = get_db_connection()
    conn.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password TEXT NOT NULL,
                        first_name TEXT NOT NULL,
                        last_name TEXT NOT NULL,
                        email TEXT NOT NULL)''')
    conn.commit()
    conn.close()

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

@app.route('/register', methods=['POST'])
def register():
    data = request.get_json()
    username = data['username']
    password = data['password']
    first_name = data['first_name']
    last_name = data['last_name']
    email = data['email']

    hashed_password = hash_password(password)

    conn = get_db_connection()

    try:
        conn.execute('INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
                     (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return jsonify({"message": "Registration succeeded"}), 201
    except sqlite3.IntegrityError:
        return jsonify({"message": "Username already exists"}), 409

    finally:
        conn.close()

if __name__ == '__main__':
    app.run(debug=True)