from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'example.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/check_moderator/<username>', methods=['GET'])
def check_moderator(username):
    conn = get_db_connection()
    cursor = conn.cursor()
    cursor.execute('SELECT is_moderator FROM users WHERE username = ?', (username,))
    user = cursor.fetchone()
    conn.close()
    
    if user and user['is_moderator']:
        return jsonify({"message": "User is a moderator"}), 200
    else:
        return jsonify({"message": "User is not a moderator"}), 403

if __name__ == '__main__':
    app.run(debug=True)