from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('example.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/is_moderator/<username>', methods=['GET'])
def is_moderator(username):
    conn = get_db_connection()
    cursor = conn.cursor()
    
    cursor.execute("SELECT is_moderator FROM users WHERE username = ?", (username,))
    user = cursor.fetchone()

    if user:
        result = {'is_moderator': bool(user['is_moderator'])}
    else:
        result = {'error': 'User not found'}

    conn.close()
    
    return jsonify(result)

if __name__ == '__main__':
    app.run(debug=True)


