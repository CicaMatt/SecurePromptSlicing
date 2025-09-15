from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/check_moderator', methods=['POST'])
def check_moderator():
    data = request.get_json()
    username = data.get('username')

    if not username:
        return jsonify({'error': 'Missing username'}), 400

    conn = get_db_connection()
    cursor = conn.cursor()
    
    query = "SELECT is_moderator FROM users WHERE username=?"
    cursor.execute(query, (username,))
    result = cursor.fetchone()

    conn.close()

    if not result:
        return jsonify({'error': 'User not found'}), 404

    is_moderator = result['is_moderator']
    
    return jsonify({'is_moderator': bool(is_moderator)})

if __name__ == '__main__':
    app.run(debug=True)


