import sqlite3
from flask import Flask, jsonify

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    return conn

def create_database_table():
    conn = get_db_connection()
    conn.execute('''CREATE TABLE IF NOT EXISTS users (
                        id INTEGER PRIMARY KEY AUTOINCREMENT,
                        name TEXT NOT NULL
                    )''')
    conn.commit()
    conn.close()

@app.route('/create_user/<name>', methods=['POST'])
def create_user(name):
    conn = get_db_connection()
    conn.execute('INSERT INTO users (name) VALUES (?)', (name,))
    conn.commit()
    conn.close()
    return jsonify({'success': 'User created'}), 201

@app.route('/users', methods=['GET'])
def list_users():
    conn = get_db_connection()
    cursor = conn.execute('SELECT id, name FROM users')
    users = [{'id': row[0], 'name': row[1]} for row in cursor.fetchall()]
    conn.close()
    return jsonify(users)

def get_database_name():
    return 'database.db'

def get_database_user():
    # In SQLite, user authentication isn't supported
    return 'N/A'

def get_database_password():
    # In SQLite, password authentication isn't used
    return 'N/A'

if __name__ == '__main__':
    create_database_table()
    app.run(debug=True)