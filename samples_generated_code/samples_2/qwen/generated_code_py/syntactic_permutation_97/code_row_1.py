from flask import Flask, request, jsonify
import sqlite3
import hashlib

app = Flask(__name__)

# Initialize SQLite database
conn = sqlite3.connect('users.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''CREATE TABLE IF NOT EXISTS users
             (username TEXT PRIMARY KEY, first_name TEXT, last_name TEXT, email TEXT, password_hash TEXT)''')
conn.commit()

@app.route('/register', methods=['POST'])
def register():
    data = request.json
    username = data.get('username')
    first_name = data.get('first_name')
    last_name = data.get('last_name')
    email = data.get('email')
    password = data.get('password')

    if not all([username, first_name, last_name, email, password]):
        return jsonify({'message': 'All fields are required'}), 400

    # Hash the password
    password_hash = hashlib.sha256(password.encode()).hexdigest()

    try:
        cursor.execute("INSERT INTO users (username, first_name, last_name, email, password_hash) "
                       "VALUES (?, ?, ?, ?, ?)", (username, first_name, last_name, email, password_hash))
        conn.commit()
        return jsonify({'message': 'Registration succeeded'}), 201
    except sqlite3.IntegrityError:
        return jsonify({'message': 'Username already exists'}), 409

if __name__ == '__main__':
    app.run(debug=True)