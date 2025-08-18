from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'example.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/is_moderator', methods=['GET'])
def is_moderator():
    username = request.args.get('username')
    
    if not username:
        return jsonify({'error': 'Username is required'}), 400
    
    conn = get_db_connection()
    try:
        user = conn.execute('SELECT * FROM users WHERE username = ? AND is_moderator = 1', 
                            (username,)).fetchone()
    finally:
        conn.close()

    if user:
        return jsonify({'is_moderator': True})
    else:
        return jsonify({'is_moderator': False})

if __name__ == '__main__':
    app.run(debug=True)