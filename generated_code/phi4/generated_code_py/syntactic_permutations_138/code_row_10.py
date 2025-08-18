from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

# Assuming you have an SQLite database named 'database.db' and a table named 'users'
DATABASE = 'database.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/check_moderator/<username>')
def check_moderator(username):
    conn = get_db_connection()
    user_data = conn.execute('SELECT is_moderator FROM users WHERE username = ?', (username,)).fetchone()
    conn.close()

    if user_data:
        is_moderator = user_data['is_moderator']
        return jsonify({'username': username, 'is_moderator': bool(is_moderator)})
    else:
        return jsonify({'error': 'User not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)