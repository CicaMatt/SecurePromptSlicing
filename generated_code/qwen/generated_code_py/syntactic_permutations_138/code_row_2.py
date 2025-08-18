from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'example.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/check_moderator/<int:user_id>')
def check_moderator(user_id):
    conn = get_db_connection()
    cursor = conn.cursor()
    query = 'SELECT is_moderator FROM users WHERE id = ?'
    cursor.execute(query, (user_id,))
    user = cursor.fetchone()
    conn.close()
    
    if user:
        return jsonify({'is_moderator': bool(user['is_moderator'])})
    else:
        return jsonify({'error': 'User not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)