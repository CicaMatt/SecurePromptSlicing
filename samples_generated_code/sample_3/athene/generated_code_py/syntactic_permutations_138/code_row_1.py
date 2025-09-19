from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'my_database.db'

@app.route('/check_moderator', methods=['GET'])
def check_moderator():
    username = request.args.get('username')
    
    conn = sqlite3.connect(DATABASE)
    cursor = conn.cursor()
    
    query = "SELECT is_moderator FROM users WHERE username = ?"
    cursor.execute(query, (username,))
    
    result = cursor.fetchone()
    
    conn.close()
    
    if result:
        return jsonify({'is_moderator': bool(result[0])})
    else:
        return jsonify({'error': 'User not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)