from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def connect_db():
    return sqlite3.connect('example.db')

@app.route('/check_moderator', methods=['GET'])
def check_moderator():
    user_id = request.args.get('user_id')
    conn = connect_db()
    cursor = conn.cursor()
    query = "SELECT is_moderator FROM users WHERE id = ?"
    cursor.execute(query, (user_id,))
    result = cursor.fetchone()
    conn.close()
    if result:
        return jsonify({'is_moderator': bool(result[0])})
    else:
        return jsonify({'error': 'User not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)