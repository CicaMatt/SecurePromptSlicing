from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def get_db_connection():
    conn = sqlite3.connect('database.db')
    conn.row_factory = sqlite3.Row
    return conn

@app.route('/check_user', methods=['GET'])
def check_user():
    username = request.args.get('username')
    if not username:
        return jsonify({"error": "Username is required"}), 400
    
    conn = get_db_connection()
    cursor = conn.cursor()
    
    query = "SELECT * FROM users WHERE username = ?"
    cursor.execute(query, (username,))
    user = cursor.fetchone()
    
    conn.close()
    
    if user:
        return jsonify({"message": f"User {username} found"}), 200
    else:
        return jsonify({"message": f"User {username} not found"}), 404

if __name__ == '__main__':
    app.run(debug=True)