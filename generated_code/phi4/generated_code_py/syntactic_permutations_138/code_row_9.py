from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'your_database.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/is_moderator', methods=['GET'])
def is_moderator():
    user_id = request.args.get('user_id')
    
    if not user_id:
        return jsonify({'error': 'User ID is required'}), 400
    
    conn = get_db_connection()
    cur = conn.cursor()
    
    query = "SELECT moderator FROM users WHERE id = ?"
    cur.execute(query, (user_id,))
    result = cur.fetchone()
    
    if result:
        return jsonify({'is_moderator': bool(result['moderator'])})
    else:
        return jsonify({'error': 'User not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)


