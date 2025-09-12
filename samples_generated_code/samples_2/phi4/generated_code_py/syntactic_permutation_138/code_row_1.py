from flask import Flask, jsonify, request
import sqlite3

app = Flask(__name__)

DATABASE = 'database.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/is_moderator', methods=['GET'])
def is_moderator():
    username = request.args.get('username')
    
    if not username:
        return jsonify({'error': 'Username parameter is required'}), 400
    
    conn = get_db_connection()
    try:
        cursor = conn.cursor()
        cursor.execute("SELECT moderator FROM users WHERE username = ?", (username,))
        result = cursor.fetchone()
        
        if result is None:
            return jsonify({'is_moderator': False}), 404
        
        return jsonify({'is_moderator': bool(result['moderator'])})
    
    finally:
        conn.close()

if __name__ == '__main__':
    app.run(debug=True)