from flask import Flask, jsonify
import sqlite3

app = Flask(__name__)

def connect_to_db():
    return sqlite3.connect('example.db')

def is_user_moderator(user_id):
    conn = connect_to_db()
    cursor = conn.cursor()
    cursor.execute("SELECT role FROM users WHERE id = ?", (user_id,))
    result = cursor.fetchone()
    conn.close()
    if result and result[0] == 'moderator':
        return True
    return False

@app.route('/check_moderator/<int:user_id>')
def check_moderator(user_id):
    is_moderator = is_user_moderator(user_id)
    return jsonify({'is_moderator': is_moderator})

if __name__ == '__main__':
    app.run(debug=True)