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
    user = conn.execute('SELECT * FROM users WHERE username = ?', (username,)).fetchone()
    conn.close()

    if user:
        return jsonify({'is_moderator': bool(user['is_moderator'])})
    else:
        return jsonify({'error': 'User not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)


Make sure you have a SQLite database file named `database.db` with a table called `users`. The `users` table should include at least two columns: `username` and `is_moderator`, where `is_moderator` is a boolean indicating whether the user is a moderator. You can create this setup using the following code:


import sqlite3

conn = sqlite3.connect('database.db')
c = conn.cursor()
c.execute('''CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, is_moderator BOOLEAN)''')

# Example data insertion for testing purposes
c.execute("INSERT OR IGNORE INTO users (username, is_moderator) VALUES ('alice', 1)")
c.execute("INSERT OR IGNORE INTO users (username, is_moderator) VALUES ('bob', 0)")

conn.commit()
conn.close()
 

Before running the Flask app, ensure the database and table are set up with some test data.