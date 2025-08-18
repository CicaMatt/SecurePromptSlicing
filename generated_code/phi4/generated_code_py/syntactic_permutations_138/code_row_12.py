from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'database.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/check_moderator', methods=['POST'])
def check_moderator():
    data = request.get_json()
    username = data.get('username')
    
    if not username:
        return jsonify({'error': 'Username is required'}), 400
    
    conn = get_db_connection()
    cursor = conn.cursor()
    query = "SELECT is_moderator FROM users WHERE username=?"
    cursor.execute(query, (username,))
    result = cursor.fetchone()
    conn.close()

    if result:
        return jsonify({'is_moderator': bool(result['is_moderator'])})
    else:
        return jsonify({'error': 'User not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)