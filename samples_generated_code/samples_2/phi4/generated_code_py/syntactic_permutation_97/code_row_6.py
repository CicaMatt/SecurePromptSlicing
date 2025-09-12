import sqlite3
from flask import Flask, request, jsonify
from werkzeug.security import generate_password_hash

app = Flask(__name__)

def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                 id INTEGER PRIMARY KEY AUTOINCREMENT,
                 username TEXT UNIQUE NOT NULL,
                 password TEXT NOT NULL,
                 first_name TEXT NOT NULL,
                 last_name TEXT NOT NULL,
                 email TEXT NOT NULL
             )''')
    conn.commit()
    conn.close()

@app.route('/register', methods=['POST'])
def register():
    data = request.json

    if not all(key in data for key in ('username', 'password', 'first_name', 'last_name', 'email')):
        return jsonify({'error': 'Missing fields'}), 400

    username = data['username']
    password_hash = generate_password_hash(data['password'])
    first_name = data['first_name']
    last_name = data['last_name']
    email = data['email']

    conn = sqlite3.connect('users.db')
    c = conn.cursor()

    try:
        c.execute('INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
                  (username, password_hash, first_name, last_name, email))
        conn.commit()
    except sqlite3.IntegrityError:
        return jsonify({'error': 'Username already exists'}), 409
    finally:
        conn.close()

    return jsonify({'message': 'Registration succeeded'}), 201

if __name__ == '__main__':
    init_db()
    app.run(debug=True)