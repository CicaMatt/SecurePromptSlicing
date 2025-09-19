from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/check_moderator', methods=['GET'])
def check_moderator():
    user_id = request.args.get('user_id')
    
    if not user_id:
        return jsonify({'error': 'Missing user_id parameter'}), 400
    
    conn = get_db_connection()
    try:
        cursor = conn.execute(
            "SELECT is_moderator FROM users WHERE id = ?", 
            (user_id,)
        )
        result = cursor.fetchone()
        
        if not result:
            return jsonify({'error': 'User not found'}), 404
        
        is_moderator = result['is_moderator']
        response = {'is_moderator': is_moderator}
    finally:
        conn.close()

    return jsonify(response)

if __name__ == '__main__':
    app.run(debug=True)