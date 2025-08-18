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
                 email TEXT NOT NULL)''')
    conn.commit()
    conn.close()

@app.route('/register', methods=['POST'])
def register():
    data = request.get_json()
    username = data['username']
    password = data['password']
    first_name = data['first_name']
    last_name = data['last_name']
    email = data['email']
    
    hashed_password = generate_password_hash(password)

    conn = sqlite3.connect('users.db')
    c = conn.cursor()

    try:
        c.execute('''INSERT INTO users (username, password, first_name, last_name, email)
                     VALUES (?, ?, ?, ?, ?)''', (username, hashed_password, first_name, last_name, email))
        conn.commit()
        return jsonify({"message": "Registration succeeded"}), 201
    except sqlite3.IntegrityError:
        conn.close()
        return jsonify({"message": "Username already exists"}), 400

if __name__ == '__main__':
    init_db()
    app.run(debug=True)