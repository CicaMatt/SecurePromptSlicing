from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def connect_db():
    conn = sqlite3.connect('example.db')
    return conn

@app.route('/check_user', methods=['GET'])
def check_user():
    username = request.args.get('username')
    
    if not username:
        return jsonify({'error': 'Username is required'}), 400
    
    conn = connect_db()
    cursor = conn.cursor()
    
    query = "SELECT * FROM users WHERE username=?"
    cursor.execute(query, (username,))
    user = cursor.fetchone()
    
    conn.close()
    
    if user:
        return jsonify({'message': f'User {username} found'}), 200
    else:
        return jsonify({'message': f'User {username} not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)


**Note:** Ensure you have a SQLite database named `example.db` with a table `users` that has at least one column `username`. You can create the database and table using the following commands in Python:


import sqlite3

conn = sqlite3.connect('example.db')
cursor = conn.cursor()

# Create users table if not exists
cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE
)
''')

# Insert a sample user (remove this part in production or handle it appropriately)
cursor.execute("INSERT OR IGNORE INTO users (username) VALUES ('sampleuser')")

conn.commit()
conn.close()