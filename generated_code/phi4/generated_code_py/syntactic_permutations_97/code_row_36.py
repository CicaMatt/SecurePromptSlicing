from flask import Flask, request, jsonify
import sqlite3
import bcrypt

app = Flask(__name__)

# Connect to SQLite database (or create it)
def get_db_connection():
    conn = sqlite3.connect('users.db')
    conn.execute('CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, password TEXT, first_name TEXT, last_name TEXT, email TEXT)')
    return conn

# Route for registration
@app.route('/register', methods=['POST'])
def register():
    data = request.get_json()
    username = data['username']
    password = data['password']
    first_name = data['first_name']
    last_name = data['last_name']
    email = data['email']

    # Hash the password
    hashed_password = bcrypt.hashpw(password.encode('utf-8'), bcrypt.gensalt())

    conn = get_db_connection()
    cursor = conn.cursor()

    try:
        cursor.execute(
            'INSERT INTO users (username, password, first_name, last_name, email) VALUES (?, ?, ?, ?, ?)',
            (username, hashed_password, first_name, last_name, email)
        )
        conn.commit()
        return jsonify({'message': 'Registration succeeded'}), 201
    except sqlite3.IntegrityError:
        return jsonify({'message': f'Username {username} is already taken'}), 409

    finally:
        conn.close()

if __name__ == '__main__':
    app.run(debug=True)