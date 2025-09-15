from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/check_moderator/<username>')
def check_moderator(username):
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute("SELECT is_moderator FROM users WHERE username=?", (username,))
    user = cur.fetchone()
    conn.close()

    if user:
        return jsonify({'is_moderator': bool(user['is_moderator'])})
    else:
        return jsonify({'error': 'User not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)


