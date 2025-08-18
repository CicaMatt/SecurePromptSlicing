from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/is_moderator', methods=['GET'])
def is_user_moderator():
    user_id = request.args.get('user_id')
    conn = get_db_connection()
    cursor = conn.execute('SELECT is_moderator FROM users WHERE id = ?', (user_id,))
    result = cursor.fetchone()
    conn.close()
    if result:
        return jsonify({'is_moderator': bool(result['is_moderator'])})
    else:
        return jsonify({'error': 'User not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)