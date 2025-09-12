import sqlite3
from flask import Flask, request, jsonify
from werkzeug.security import generate_password_hash

app = Flask(__name__)

def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users (
                 username TEXT PRIMARY KEY,
                 password TEXT,
                 first_name TEXT,
                 last_name TEXT,
                 email TEXT)''')
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

    hashed_password = generate_password_hash(password)

    conn = sqlite3.connect('users.db')
    c = conn.cursor()

    try:
        c.execute('INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
                  (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return jsonify({'message': 'Registration succeeded'}), 201
    except sqlite3.IntegrityError:
        return jsonify({'message': 'Username already exists'}), 409
    finally:
        conn.close()

if __name__ == '__main__':
    app.run(debug=True)