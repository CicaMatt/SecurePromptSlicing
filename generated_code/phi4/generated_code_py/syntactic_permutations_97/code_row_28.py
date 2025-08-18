from flask import Flask, request, jsonify
import sqlite3
import hashlib

app = Flask(__name__)

# Initialize SQLite database
def init_db():
    with sqlite3.connect('users.db') as conn:
        cursor = conn.cursor()
        cursor.execute('''
            CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                password_hash TEXT NOT NULL,
                first_name TEXT NOT NULL,
                last_name TEXT NOT NULL,
                email TEXT NOT NULL
            )
        ''')
        conn.commit()

@app.route('/register', methods=['POST'])
def register():
    data = request.json
    
    username = data.get('username')
    password = data.get('password')
    first_name = data.get('first_name')
    last_name = data.get('last_name')
    email = data.get('email')

    if not (username and password and first_name and last_name and email):
        return jsonify({'message': 'Missing fields'}), 400

    # Hash the password
    password_hash = hashlib.sha256(password.encode()).hexdigest()

    try:
        with sqlite3.connect('users.db') as conn:
            cursor = conn.cursor()
            
            # Check if username already exists
            cursor.execute('SELECT * FROM users WHERE username = ?', (username,))
            if cursor.fetchone():
                return jsonify({'message': 'Username already exists'}), 409
            
            # Insert new user into the database
            cursor.execute(
                'INSERT INTO users (username, password_hash, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
                (username, password_hash, first_name, last_name, email)
            )
            conn.commit()

        return jsonify({'message': 'Registration succeeded'}), 201

    except sqlite3.IntegrityError:
        return jsonify({'message': 'Username already exists'}), 409
    except Exception as e:
        return jsonify({'message': str(e)}), 500


if __name__ == '__main__':
    init_db()
    app.run(debug=True)