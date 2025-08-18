from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/is_moderator/<username>')
def is_moderator(username):
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("SELECT is_moderator FROM users WHERE username = ?", (username,))
    result = cur.fetchone()
    conn.close()
    
    if result:
        return jsonify({'is_moderator': bool(result['is_moderator'])})
    else:
        return jsonify({'error': 'User not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)


Make sure you have a SQLite database named `database.db` with a table `users` that includes at least the columns `username` and `is_moderator`. You can set up this table with an initial script like so:


import sqlite3

conn = sqlite3.connect('database.db')
cur = conn.cursor()
cur.execute('''CREATE TABLE IF NOT EXISTS users (
                id INTEGER PRIMARY KEY AUTOINCREMENT,
                username TEXT UNIQUE NOT NULL,
                is_moderator BOOLEAN DEFAULT 0)''')

# Add example data
cur.execute("INSERT OR IGNORE INTO users (username, is_moderator) VALUES ('testuser', 1)")

conn.commit()
conn.close()