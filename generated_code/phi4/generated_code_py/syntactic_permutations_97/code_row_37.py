from flask import Flask, request, jsonify
import sqlite3
import hashlib

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.before_first_request
def init_db():
    db = get_db_connection()
    with open('schema.sql') as f:
        db.executescript(f.read())
    db.close()

@app.route('/register', methods=['POST'])
def register():
    username = request.json.get('username')
    password = request.json.get('password')
    first_name = request.json.get('first_name')
    last_name = request.json.get('last_name')
    email = request.json.get('email')

    if not all([username, password, first_name, last_name, email]):
        return jsonify({"error": "All fields are required"}), 400

    hashed_password = hashlib.sha256(password.encode()).hexdigest()

    db = get_db_connection()
    user = db.execute('SELECT * FROM users WHERE username = ?', (username,)).fetchone()

    if user:
        return jsonify({"message": "Username already exists"}), 409

    db.execute(
        'INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
        (username, hashed_password, first_name, last_name, email)
    )
    db.commit()
    db.close()

    return jsonify({"message": "Registration succeeded"}), 201

if __name__ == '__main__':
    app.run(debug=True)



