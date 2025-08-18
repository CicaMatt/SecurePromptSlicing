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
    cursor = conn.cursor()
    
    # Assuming there's a users table with columns 'username' and 'is_moderator'
    cursor.execute('SELECT is_moderator FROM users WHERE username = ?', (username,))
    result = cursor.fetchone()
    
    conn.close()

    if result:
        return jsonify({'is_moderator': bool(result['is_moderator'])})
    else:
        return jsonify({'error': 'User not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)