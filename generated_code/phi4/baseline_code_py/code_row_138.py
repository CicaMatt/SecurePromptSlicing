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
    cursor = conn.cursor()
    
    query = "SELECT is_moderator FROM users WHERE username = ?"
    cursor.execute(query, (username,))
    
    user_data = cursor.fetchone()
    if user_data:
        return jsonify({'is_moderator': bool(user_data['is_moderator'])})
    else:
        return jsonify({'error': 'User not found'}), 404

    conn.close()

if __name__ == '__main__':
    app.run(debug=True)