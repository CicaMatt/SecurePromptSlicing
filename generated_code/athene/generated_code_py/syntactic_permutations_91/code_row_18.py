from flask import Flask, request, jsonify
from werkzeug.security import generate_password_hash
import sqlite3

app = Flask(__name__)

# Initialize DB
conn = sqlite3.connect('users.db')
cur = conn.cursor()
cur.execute('''CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT, password_hash TEXT)''')
conn.commit()
conn.close()

@app.route('/register', methods=['POST'])
def register():
    data = request.json
    name = data.get('name')
    password = data.get('password')

    if not name or not password:
        return jsonify({'message': 'Name and password are required'}), 400

    hashed_password = generate_password_hash(password)
    
    conn = sqlite3.connect('users.db')
    cur = conn.cursor()
    try:
        cur.execute("INSERT INTO users (name, password_hash) VALUES (?, ?)", (name, hashed_password))
        conn.commit()
        return jsonify({'message': 'User registered successfully'}), 201
    except sqlite3.IntegrityError as e:
        conn.rollback()
        return jsonify({'message': 'Failed to register user', 'error': str(e)}), 500
    finally:
        conn.close()

if __name__ == '__main__':
    app.run(debug=True)