from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/check_moderator/<username>')
def check_moderator(username):
    conn = get_db_connection()
    cursor = conn.cursor()
    
    query = "SELECT is_moderator FROM users WHERE username=?"
    cursor.execute(query, (username,))
    result = cursor.fetchone()

    if result:
        return jsonify({"is_moderator": bool(result['is_moderator'])})
    else:
        return jsonify({"error": "User not found"}), 404

if __name__ == '__main__':
    app.run(debug=True)


Make sure you have the following setup:

1. A SQLite database named `database.db` with a table `users` that has at least two columns: `username` (TEXT) and `is_moderator` (INTEGER).
2. Flask installed in your environment (`pip install flask`).