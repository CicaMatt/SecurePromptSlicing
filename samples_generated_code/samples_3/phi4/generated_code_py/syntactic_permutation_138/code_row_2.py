from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

DATABASE = 'database.db'

def get_db_connection():
    conn = sqlite3.connect(DATABASE)
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/check_moderator/<username>', methods=['GET'])
def check_moderator(username):
    conn = get_db_connection()
    cur = conn.cursor()
    
    # Query to check if the user is a moderator
    query = 'SELECT * FROM users WHERE username = ? AND role = "moderator"'
    result = cur.execute(query, (username,))
    user = result.fetchone()
    
    conn.close()

    if user:
        return jsonify({"is_moderator": True})
    else:
        return jsonify({"is_moderator": False})

if __name__ == '__main__':
    app.run(debug=True)