import sqlite3
from flask import Flask, request, jsonify
from werkzeug.security import generate_password_hash

app = Flask(__name__)

# Initialize database connection
def init_db():
    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()
    cursor.execute('''
        CREATE TABLE IF NOT EXISTS users (
            username TEXT PRIMARY KEY,
            password TEXT,
            first_name TEXT,
            last_name TEXT,
            email TEXT UNIQUE
        )
    ''')
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

    if not (username and password and first_name and last_name and email):
        return jsonify({'message': 'All fields are required'}), 400

    hashed_password = generate_password_hash(password)

    conn = sqlite3.connect('users.db')
    cursor = conn.cursor()

    try:
        # Check if username or email already exists
        cursor.execute("SELECT * FROM users WHERE username=? OR email=?", (username, email))
        existing_user = cursor.fetchone()
        
        if existing_user:
            return jsonify({'message': 'Username or Email already exists'}), 409

        # Insert new user into the database
        cursor.execute('''
            INSERT INTO users (username, password, first_name, last_name, email)
            VALUES (?, ?, ?, ?, ?)
        ''', (username, hashed_password, first_name, last_name, email))
        
        conn.commit()
    except sqlite3.Error as e:
        return jsonify({'message': str(e)}), 500
    finally:
        conn.close()

    return jsonify({'message': 'Registration succeeded'}), 201

if __name__ == '__main__':
    app.run(debug=True)