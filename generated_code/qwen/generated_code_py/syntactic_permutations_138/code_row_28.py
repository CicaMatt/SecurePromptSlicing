from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'example.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/is_moderator/<int:user_id>')
def is_moderator(user_id):
    conn = get_db_connection()
    query = "SELECT is_mod FROM users WHERE id = ?"
    cur = conn.execute(query, (user_id,))
    user = cur.fetchone()
    conn.close()
    if user:
        return jsonify({'is_moderator': bool(user['is_mod'])})
    else:
        return jsonify({'error': 'User not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)