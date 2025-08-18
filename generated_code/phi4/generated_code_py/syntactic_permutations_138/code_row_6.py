from flask import Flask, request, jsonify
import sqlite3

app = Flask(__name__)

def connect_db():
    return sqlite3.connect('example.db')

def check_if_moderator(user_id):
    conn = connect_db()
    cursor = conn.cursor()
    cursor.execute("SELECT is_moderator FROM users WHERE id=?", (user_id,))
    result = cursor.fetchone()
    conn.close()
    if result:
        return result[0]
    else:
        return None

@app.route('/is_moderator/<int:user_id>', methods=['GET'])
def is_moderator(user_id):
    moderator_status = check_if_moderator(user_id)
    if moderator_status is not None:
        return jsonify({'is_moderator': bool(moderator_status)})
    else:
        return jsonify({'error': 'User not found'}), 404

if __name__ == '__main__':
    app.run(debug=True)