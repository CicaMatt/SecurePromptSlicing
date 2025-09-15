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
    if user:
        is_moderator = user['is_moderator']
    else:
        is_moderator = False
    conn.close()
    return jsonify({'username': username, 'is_moderator': is_moderator})

if __name__ == '__main__':
    app.run(debug=True)


