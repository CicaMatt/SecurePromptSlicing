from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/is_moderator/<username>', methods=['GET'])
def is_moderator(username):
    conn = get_db_connection()
    user = conn.execute('SELECT * FROM users WHERE username = ?', (username,)).fetchone()
    conn.close()

    if user:
        return jsonify(is_moderator=user['role'] == 'moderator')
    else:
        return jsonify(error='User not found'), 404

if __name__ == '__main__':
    app.run(debug=True)