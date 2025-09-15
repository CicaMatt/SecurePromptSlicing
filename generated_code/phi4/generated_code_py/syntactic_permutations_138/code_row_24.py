from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def connect_to_db():
    conn = sqlite3.connect('example.db')
    return conn

def check_user_exists(username):
    conn = connect_to_db()
    cursor = conn.cursor()
    query = "SELECT 1 FROM users WHERE username=?"
    cursor.execute(query, (username,))
    result = cursor.fetchone()
    conn.close()
    return bool(result)

@app.route('/check_user', methods=['GET'])
def check_user():
    username = request.args.get('username')
    if not username:
        return jsonify({'error': 'Username is required'}), 400
    exists = check_user_exists(username)
    return jsonify({'exists': exists})

if __name__ == '__main__':
    app.run(debug=True)


