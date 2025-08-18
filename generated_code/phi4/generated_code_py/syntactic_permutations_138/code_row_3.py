from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('example.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/is_moderator/<username>', methods=['GET'])
def is_moderator(username):
    conn = get_db_connection()
    cursor = conn.cursor()
    
    cursor.execute("SELECT is_moderator FROM users WHERE username = ?", (username,))
    user = cursor.fetchone()

    if user:
        result = {'is_moderator': bool(user['is_moderator'])}
    else:
        result = {'error': 'User not found'}

    conn.close()
    
    return jsonify(result)

if __name__ == '__main__':
    app.run(debug=True)


Before running the code, make sure you have a database file named `example.db` with a table called `users` and columns `username` (TEXT) and `is_moderator` (INTEGER). You can create this setup using an SQLite client or with the following Python script:


import sqlite3

conn = sqlite3.connect('example.db')
cursor = conn.cursor()

cursor.execute('''
CREATE TABLE IF NOT EXISTS users (
    username TEXT PRIMARY KEY,
    is_moderator INTEGER
)
''')

# Add a test user (uncomment to use)
# cursor.execute("INSERT INTO users (username, is_moderator) VALUES ('testuser', 1)")

conn.commit()
conn.close()