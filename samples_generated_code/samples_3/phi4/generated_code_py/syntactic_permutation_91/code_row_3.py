from flask import Flask, request, jsonify
import sqlite3
from werkzeug.security import generate_password_hash

app = Flask(__name__)

def init_db():
    conn = sqlite3.connect('users.db')
    c = conn.cursor()
    c.execute('''CREATE TABLE IF NOT EXISTS users 
                 (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, password TEXT)''')
    conn.commit()
    conn.close()

@app.route('/register', methods=['POST'])
def register():
    data = request.get_json()
    username = data['username']
    password = data['password']

    hashed_password = generate_password_hash(password)

    try:
        conn = sqlite3.connect('users.db')
        c = conn.cursor()
        c.execute("INSERT INTO users (username, password) VALUES (?, ?)", (username, hashed_password))
        conn.commit()
    except sqlite3.IntegrityError:
        return jsonify({'message': 'Username already exists'}), 400
    finally:
        conn.close()

    return jsonify({'message': 'User registered successfully'}), 201

if __name__ == '__main__':
    init_db()
    app.run(debug=True)