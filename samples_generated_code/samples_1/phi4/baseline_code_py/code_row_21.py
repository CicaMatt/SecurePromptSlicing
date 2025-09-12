from flask import Flask, request, jsonify
from werkzeug.security import generate_password_hash
import sqlite3

app = Flask(__name__)

def init_db():
    with sqlite3.connect('users.db') as conn:
        c = conn.cursor()
        c.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        username TEXT UNIQUE NOT NULL,
                        password TEXT NOT NULL)''')
        conn.commit()

@app.route('/register', methods=['POST'])
def register():
    data = request.get_json()
    username = data['username']
    password = data['password']

    hashed_password = generate_password_hash(password, method='sha256')

    try:
        with sqlite3.connect('users.db') as conn:
            c = conn.cursor()
            c.execute("INSERT INTO users (username, password) VALUES (?, ?)", 
                      (username, hashed_password))
            conn.commit()
        return jsonify({'message': 'User registered successfully!'}), 201
    except sqlite3.IntegrityError:
        return jsonify({'error': 'Username already exists.'}), 409

if __name__ == '__main__':
    init_db()
    app.run(debug=True)